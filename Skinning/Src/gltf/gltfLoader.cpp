#include "gltfLoader.h"
#include <iostream>

namespace GLTFHelpers {
	Transform GetLocalTransform(cgltf_node& node) {
		Transform result;

		if (node.has_matrix) {
			glm::mat4 mat(node.matrix[0]);
			//result = mat4ToTransform(mat);
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
	uint32_t boneCount = data->nodes_count;
	Pose result(boneCount);

	for (uint32_t i = 0; i < boneCount; i++) {
		cgltf_node* node = &(data->nodes[i]);
		Transform transform = GLTFHelpers::GetLocalTransform(data->nodes[i]);
		result.SetLocalTransform(i, transform);
		uint32_t parent = GLTFHelpers::GetNodeIndex(node->parent, data->nodes, boneCount);
		result.SetParent(i, parent);
	}
}