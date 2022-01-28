#include "debugDraw.h"

DebugDraw::DebugDraw() {

	_attributes = new Attribute<glm::vec3>();
	_shader = new Shader("Shaders/animation.vert", "Shaders/animation.frag");
}

DebugDraw::DebugDraw(uint32_t size) {

	_attributes = new Attribute<glm::vec3>();
	_shader = new Shader("Shaders/animation.vert", "Shaders/animation.frag");
}

DebugDraw::~DebugDraw(){
	delete _attributes;
	delete _shader;
}

void DebugDraw::Resize(uint32_t size) {
	_points.resize(size);
}

void DebugDraw::SetPose(Pose& pose) {
	unsigned int requiredVerts = 0;
	unsigned int numJoints = pose.GetSize();

	for (unsigned int i = 0; i < numJoints; ++i) {
		if (pose.GetParent(i) < 0) {
			continue;
		}

		requiredVerts += 2;
	}

	_points.resize(requiredVerts);
	for (unsigned int i = 0; i < numJoints; ++i) {
		if (pose.GetParent(i) < 0) {
			continue;
		}

		_points.push_back(pose.GetGlobalTransform(i).position);
		_points.push_back(pose.GetGlobalTransform(pose.GetParent(i)).position);
	}

	_attributes->Set(_points);
}

void DebugDraw::Draw(DebugDrawMode mode, const glm::vec3& color, const glm::mat4& mvp) {
	_shader->Bind();
	Uniform<glm::mat4>::Set(_shader->GetUniformIndex("mvp"), mvp);
	Uniform<glm::vec3>::Set(_shader->GetUniformIndex("color"), color);
	_attributes->BindTo(_shader->GetAttributeIndex("position"));
	if (mode == DebugDrawMode::Lines) {
		ExecuteDraw(_attributes->GetCount(), DrawMode::Lines);
	}
	else if (mode == DebugDrawMode::Loop) {
		ExecuteDraw(_attributes->GetCount(), DrawMode::LineLoop);
	}
	else if (mode == DebugDrawMode::Strip) {
		ExecuteDraw(_attributes->GetCount(), DrawMode::LineStrip);
	}
	else {
		ExecuteDraw(_attributes->GetCount(), DrawMode::Points);
	}
	_attributes->UnBind(_shader->GetAttributeIndex("position"));
	_shader->UnBind();

}