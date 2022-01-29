#include "graph.h"
#include <cstdarg>
#include "gltfLoader.h"

void Graph::Initialize() {

	cgltf_data* gltf = LoadGLTFFile("Assets/Woman.gltf");
	_restPose = LoadRestPose(gltf);
	_clips = LoadAnimationClips(gltf);
	FreeGLTFFile(gltf);
	_restPoseDraw = new DebugDraw();
	_restPoseDraw->SetPose(_restPose);

	_currentClip = 0;
	_currentPose = _restPose;

	_currentPoseDraw = new DebugDraw();
	_currentPoseDraw->SetPose(_currentPose);

	//walkingのアニメーションを取り出す
	uint32_t numUIClips = (uint32_t)_clips.size();
	for (unsigned int i = 0; i < numUIClips; ++i) {
		if (_clips[i].GetName() == "Walking") {
			_currentClip = i;
			break;
		}
	}
}

void Graph::Update(float deltaTime) {
	_time = _clips[_currentClip].Sample(_currentPose, _time + deltaTime);
	_currentPoseDraw->SetPose(_currentPose);
}

void Graph::Render(float aspectRatio) {
	glm::mat4 projection = glm::perspective(glm::radians(60.0f), aspectRatio, 0.01f, 1000.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(0, 4, 7), glm::vec3(0, 4, 0), glm::vec3(0, 1, 0));
	glm::mat4 mvp = projection * view;

	_restPoseDraw->Draw(DebugDrawMode::Lines, glm::vec3(1, 0, 0), mvp);
	_currentPoseDraw->Draw(DebugDrawMode::Lines, glm::vec3(0, 0, 1), mvp);
}

void Graph::ShutDown() {
	delete _restPoseDraw;
	delete _currentPoseDraw;
	_clips.clear();
}

