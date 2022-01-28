#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>

struct Transform {
	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;
	Transform():
		position(glm::vec3(0,0,0)),
		rotation(glm::quat(0,0,0,1)),
		scale(glm::vec3(1,1,1)){}
	Transform(const glm::vec3& p, const glm::quat& r, const glm::vec3& s):
		position(p),
		rotation(r),
		scale(s){}
};

Transform Combine(const Transform& a, const Transform& b);
Transform Mat4ToTransform(const glm::mat4& m);
glm::mat4 TransformToMat4(const Transform& t);
bool operator==(const Transform& a, const Transform& b);
bool operator!=(const Transform& a, const Transform& b);
