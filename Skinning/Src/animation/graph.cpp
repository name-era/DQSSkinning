#include "graph.h"
#include <cstdarg>
#include "gltfLoader.h"

ScalarTrack Graph::MakeScalarTrack(Interpolation interp, uint32_t numFrames, ...) {
	ScalarTrack result;
	result.SetInterpolation(interp);
	result.Resize(numFrames);

	va_list args;
	va_start(args, numFrames);

	//引数の数分追加する
	for (uint32_t i = 0; i < numFrames; i++) {
		result[i] = va_arg(args, ScalarFrame);
	}

	va_end(args);
	return result;
}

ScalarFrame Graph::MakeFrame(float time, float in, float value, float out) {
	ScalarFrame result;
	result.time = time;
	result.in[0] = in;
	result.value[0] = value;
	result.out[0] = out;
	return result;
}

ScalarFrame Graph::MakeFrame(float time, float value) {
	return MakeFrame(time, 0.0f, value, 0.0f);
}

VectorFrame Graph::MakeFrame(float time, const glm::vec3& in, const glm::vec3& value, const glm::vec3& out) {
	VectorFrame result;
	result.time = time;
	result.in[0] = in.x;
	result.in[1] = in.y;
	result.in[2] = in.z;
	result.value[0] = value.x;
	result.value[1] = value.y;
	result.value[2] = value.z;
	result.out[0] = out.x;
	result.out[1] = out.y;
	result.out[2] = out.z;
	return result;
}

VectorFrame Graph::MakeFrame(float time, const glm::vec3& value) {
	return MakeFrame(time, glm::vec3(), value, glm::vec3());
}

QuartanionFrame Graph::MakeFrame(float time, const glm::quat& in, const glm::quat& out, const glm::quat& value) {
	QuartanionFrame result;
	
	result.time = time;
	result.in[0] = in.x;
	result.in[0] = in.y;
	result.in[0] = in.z;
	result.in[0] = in.w;
	result.value[0] = value.x;
	result.value[1] = value.y;
	result.value[2] = value.z;
	result.value[3] = value.w;
	result.out[0] = out.x;
	result.out[1] = out.y;
	result.out[2] = out.z;
	result.out[3] = out.w;
	return result;

}

QuartanionFrame Graph::MakeFrame(float time, const glm::quat& value) {
	return MakeFrame(time, glm::quat(0, 0, 0, 0), value, glm::quat(0, 0, 0, 0));
}

void Graph::Initialize() {

	cgltf_data* gltf = LoadGLTFFile("Assets/Woman.gltf");
	_restPose = LoadRestPose(gltf);
	_clips = LoadAnimationClips(gltf);
	FreeGLTFFile(gltf);
	_restPoseDraw = new DebugDraw();
	_restPoseDraw->SetPose(_restPose);

	_currentClip = 0;
	_currentPose = _restPose;

	_currentPoseDraw->SetPose(_currentPose);

	//walkingのアニメーションを取り出す
	uint32_t numUIClips = _clips.size();
	for (unsigned int i = 0; i < numUIClips; ++i) {
		if (_clips[i].GetName() == "Walking") {
			_currentClip = i;
			break;
		}
	}

}

void Graph::Render(float aspectRatio) {

}

void Graph::ShutDown() {
	delete _restPoseDraw;
	delete _currentPoseDraw;
	_clips.clear();
}

