#include "transform.h"

Transform Combine(const Transform& parent, const Transform& child) {
	
	Transform out;

	out.scale = parent.scale * child.scale;
	out.rotation = parent.rotation * child.rotation;

	//scale, rotation, translationÇÃèáÇ≈ïœä∑ÇçsÇ§
	//rotation * scale
	out.position = parent.rotation * (parent.scale * child.position);
	//translation
	out.position = parent.position + out.position;

	return out;
}

Transform Mat4ToTransform(const glm::mat4& m) {

	Transform out;
	
	//out.position = glm::vec3(m[0][3], m[1][3], m[2][3]);
	//glm::mat4 rotMatrix=glm::lookAt(vec3()
	//out.rotation = glm::quat_cast(m);

	//mat4 rotScaleMat(
	//	m.v[0], m.v[1], m.v[2], 0,
	//	m.v[4], m.v[5], m.v[6], 0,
	//	m.v[8], m.v[9], m.v[10], 0,
	//	0, 0, 0, 1
	//);
	//mat4 invRotMat = quatToMat4(inverse(out.rotation));
	//mat4 scaleSkewMat = rotScaleMat * invRotMat;

	//out.scale = vec3(
	//	scaleSkewMat.v[0],
	//	scaleSkewMat.v[5],
	//	scaleSkewMat.v[10]
	//);

	return out;
}

glm::mat4 TransformToMat4(const Transform& t) {
	glm::vec3 x = t.rotation * glm::vec3(1, 0, 0);
	glm::vec3 y = t.rotation * glm::vec3(0, 1, 0);
	glm::vec3 z = t.rotation * glm::vec3(0, 0, 1);

	x *= glm::vec3(t.scale.x);
	y *= glm::vec3(t.scale.y);
	z *= glm::vec3(t.scale.z);

	glm::vec3 p = t.position;

	glm::mat4 result = glm::mat4(
		x.x, y.x, z.x, p.x,
		x.y, y.y, z.y, p.y,
		x.z, y.z, z.z, p.z,
		0, 0, 0, 1);

	return result;
}

bool operator==(const Transform& a, const Transform& b) {
	return a.position == b.position && a.rotation == b.rotation && a.scale == b.scale;
}

bool operator!=(const Transform& a, const Transform& b) {
	return !(a == b);
}