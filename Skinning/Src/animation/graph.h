#pragma once
#define PI 3.14159265359

#include "appBase.h"
#include "track.h"
#include "uniform.h"
#include "draw.h"
#include "pose.h"
#include "animationClip.h"
#include "debugDraw.h"

#include <vector>
#include <glm/gtc/type_ptr.hpp>


class Graph : public Application {
protected:
	Pose _restPose;
	std::vector<AnimationClip> _clips;

	DebugDraw* _restPoseDraw;
	DebugDraw* _currentPoseDraw;

	uint32_t _currentClip;
	Pose _currentPose;

	float _time;

public:

	enum class GraphDrawMode {
		Lines, Loop, Strip, Points
	};

	void Initialize();
	void Update(float deltaTime);
	void Render(float aspectRatio);
	void ShutDown();
};