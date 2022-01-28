#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "attribute.h"
#include "shader.h"
#include "pose.h"

class DebugDraw {
	enum class DrawMode
	{
		Lines, Loop, Strip, Points
	};

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
	void FromPose(Pose& pose);
};