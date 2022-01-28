#include "debugDraw.h"

DebugDraw::DebugDraw() {

	_attributes = new Attribute<glm::vec3>();
	_shader = new Shader("Shaders/animation.vert", "Shaders/animation.frag");
}

DebugDraw::DebugDraw(uint32_t size) {

	_attributes = new Attribute<glm::vec3>();
	_shader = new Shader("Shaders/animation.vert", "Shaders/animation.frag");
}

void DebugDraw::Resize(uint32_t size) {
	_points.resize(size);
}

void DebugDraw::FromPose(Pose& pose) {
	unsigned int requiredVerts = 0;
	unsigned int numJoints = pose.GetSize();

	for (unsigned int i = 0; i < numJoints; ++i) {
		if (pose.GetParent(i) < 0) {
			continue;
		}

		requiredVerts += 2;
	}

	mPoints.resize(requiredVerts);
	for (unsigned int i = 0; i < numJoints; ++i) {
		if (pose.GetParent(i) < 0) {
			continue;
		}

		mPoints.push_back(pose.GetGlobalTransform(i).position);
		mPoints.push_back(pose.GetGlobalTransform(pose.GetParent(i)).position);
	}
}