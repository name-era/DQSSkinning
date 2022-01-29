#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "attribute.h"
#include "shader.h"
#include "pose.h"
#include "uniform.h"
#include "draw.h"

#include <glm/glm.hpp>

enum class DebugDrawMode
{
	Lines, Loop, Strip, Points
};

class DebugDraw {
protected:
	std::vector<glm::vec3> _points;
	Attribute<glm::vec3>* _attributes;
	Shader* _shader;

private:
	DebugDraw(const DebugDraw&);
	DebugDraw& operator=(const DebugDraw&);

public:

	DebugDraw();
	DebugDraw(uint32_t size);
	~DebugDraw();


	void Resize(uint32_t size);
	void SetPose(Pose& pose);
	void Draw(DebugDrawMode mode, const glm::vec3& color, const glm::mat4& mvp);

};