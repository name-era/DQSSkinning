#pragma once

#include "appBase.h"
#include "track.h"
#include "shader.h"
#include "attribute.h"
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

private:
	ScalarTrack MakeScalarTrack(Interpolation interp, uint32_t numFrames, ...);
	ScalarFrame MakeFrame(float time, float in, float value, float out);
	ScalarFrame MakeFrame(float time, float value);
	VectorFrame MakeFrame(float time, const glm::vec3& in, const glm::vec3& value, const glm::vec3& out);
	VectorFrame MakeFrame(float time, const glm::vec3& value);
	QuartanionFrame MakeFrame(float time, const glm::quat& in, const glm::quat& out, const glm::quat& value);
	QuartanionFrame MakeFrame(float time, const glm::quat& value);

public:

	enum class GraphDrawMode {
		Lines, Loop, Strip, Points
	};

	void Initialize();
	void Update();
	void Render(float aspectRatio);
	void ShutDown();
};