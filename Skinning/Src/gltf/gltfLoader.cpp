#include "gltfLoader.h"
#include <iostream>

namespace GLTFHelpers {
	Transform GetLocalTransform(cgltf_node& node) {
		Transform result;

		if (node.has_matrix) {
			//glm::mat4 mat(node.matrix[0]);
			//result = mat4ToTransform(mat);
			//とりあえず考えない
		}

		if (node.has_translation) {
			result.position = glm::vec3(node.translation[0], node.translation[1], node.translation[2]);
		}

		if (node.has_rotation) {
			result.rotation = glm::quat(node.rotation[0], node.rotation[1], node.rotation[2], node.rotation[3]);
		}

		if (node.has_scale) {
			result.scale = glm::vec3(node.scale[0], node.scale[1], node.scale[2]);
		}

		return result;
	}

	uint32_t GetNodeIndex(cgltf_node* target, cgltf_node* allNodes, uint32_t numNodes) {
		if (target == 0) {
			return -1;
		}
		for (uint32_t i = 0; i < numNodes; i++) {
			if (target == &allNodes[i]) {
				return i;
			}
		}
		return -1;
	}

	void GetScalarValues(std::vector<float>& outScalars, uint32_t inComponentCount, const cgltf_accessor& inAccessor) {
		outScalars.resize(inAccessor.count * inComponentCount);
		for (cgltf_size i = 0; i < inAccessor.count; i++) {
			cgltf_accessor_read_float(&inAccessor, i, &outScalars[i * inComponentCount], inComponentCount);
		}
	}

	template<typename T, int N>
	void TrackFromChannel(Track<T, N>& inOutTrack, const cgltf_animation_channel& inChannel) {
		cgltf_animation_sampler& sampler = *inChannel.sampler;

		Interpolation interpolation = Interpolation::Constant;
		if (inChannel.sampler->interpolation == cgltf_interpolation_type_linear) {
			interpolation = Interpolation::Linear;
		}
		else if (inChannel.sampler->interpolation == cgltf_interpolation_type_cubic_spline) {
			interpolation = Interpolation::Cubic;	
		}

		bool isSamplerCubic = (interpolation == Interpolation::Cubic);
		inOutTrack.SetInterpolation(interpolation);

		std::vector<float> timelineFloats;
		GetScalarValues(timelineFloats, 1, *sampler.input);

		std::vector<float> valueFloats;
		GetScalarValues(valueFloats, N, *sampler.output);

		uint32_t numFrames = (uint32_t)sampler.input->count;
		uint32_t numberOfValuesPerFrame = (uint32_t)(valueFloats.size() / timelineFloats.size());
		inOutTrack.Resize(numFrames);


		for (uint32_t i = 0; i < numFrames; i++) {
			//1フレームごとの値の数×フレーム数
			int baseIndex = i * numberOfValuesPerFrame;
			Frame<N>& frame = inOutTrack[i];
			int offset = 0;
			frame.time = timelineFloats[i];

			//キュービック補間であればinとoutに値を入れておく
			for (int component = 0; component < N; component++) {
				frame.in[component] = isSamplerCubic ? valueFloats[baseIndex + offset++] : 0.0f;
			}
			for (int component = 0; component < N; component++) {
				frame.value[component] = valueFloats[baseIndex + offset++];
			}
			for (int component = 0; component < N; component) {
				frame.out[component] = isSamplerCubic ? valueFloats[baseIndex + offset++] : 0.0f;
			}
		}
	}
}

cgltf_data* LoadGLTFFile(const char* path) {
	cgltf_options options;
	memset(&options, 0, sizeof(cgltf_options));
	cgltf_data* data = NULL;

	cgltf_result result = cgltf_parse_file(&options, path, &data);
	if (result != cgltf_result_success) {
		std::cout << "could not load input file.\n";
		return 0;
	}

	result = cgltf_load_buffers(&options, data, path);
	if (result != cgltf_result_success) {
		std::cout << "could not load buffers.\n";
		return 0;
	}

	result = cgltf_validate(data);
	if (result != cgltf_result_success) {
		std::cout << "invalid gltf file.\n";
		return 0;
	}

	return data;
}

void FreeGLTFFile(cgltf_data* data) {
	if (data == 0) {
		std::cout << "can't free null data\n";
	}
	else {
		cgltf_free(data);
	}
}

Pose LoadRestPose(cgltf_data* data) {
	uint32_t boneCount = (uint32_t)data->nodes_count;
	Pose result(boneCount);

	for (uint32_t i = 0; i < boneCount; i++) {
		cgltf_node* node = &(data->nodes[i]);
		Transform transform = GLTFHelpers::GetLocalTransform(data->nodes[i]);
		result.SetLocalTransform(i, transform);
		int parent = GLTFHelpers::GetNodeIndex(node->parent, data->nodes, boneCount);
		result.SetParent(i, parent);
	}

	return result;
}

std::vector<AnimationClip> LoadAnimationClips(cgltf_data* data) {
	uint32_t numClips = (uint32_t)data->animations_count;
	uint32_t numNodes = (uint32_t)data->nodes_count;

	std::vector<AnimationClip> result;
	result.resize(numClips);

	for (uint32_t i = 0; i < numClips; i++) {
		//アニメーションの名前を保存
		result[i].SetName(data->animations[i].name);
		uint32_t numChannels = (uint32_t)data->animations[i].channels_count;

		//channel：アニメーションさせるnodeとその詳細を指定する
		for (uint32_t j = 0; j < numChannels; j++) {
			cgltf_animation_channel& channel = data->animations[i].channels[j];
			cgltf_node* target = channel.target_node;
			int nodeId = GLTFHelpers::GetNodeIndex(target, data->nodes, numNodes);
			if (channel.target_path == cgltf_animation_path_type_translation) {
				VectorTrack& track = result[i][nodeId].GetPositionTrack();
				GLTFHelpers::TrackFromChannel<glm::vec3, 3>(track, channel);
			}
			else if (channel.target_path == cgltf_animation_path_type_scale) {
				VectorTrack& track = result[i][nodeId].GetScaleTrack();
				GLTFHelpers::TrackFromChannel<glm::vec3, 3>(track, channel);
			}
			else if (channel.target_path == cgltf_animation_path_type_rotation) {
				QartanionTrack& track = result[i][nodeId].GetRotationTrack();
				GLTFHelpers::TrackFromChannel<glm::quat, 4>(track, channel);
			}
		}
		result[i].RecalculateDuration();
	}
	return result;
}