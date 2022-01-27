#include "transform.h"

Transform Combine(const Transform& a, const Transform& b) {
	Transform out;
	//scale, rotation, translationÇÃèáÇ≈ïœä∑ÇçsÇ§
	out.scale = a.scale * b.scale;
	out.rotation = b.rotation * a.rotation;

	//rotation * scale
	out.position = a.rotation * (a.scale * b.position);
	//translation
	out.position = a.position + out.position;

	return out;
}

Transform Mat4ToTransform(const glm::mat4& m) {

	Transform out;
	out.position = glm::vec3(m[12], m[13], m[14]);
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

	x *= t.scale.x;
	y *= t.scale.y;
	z *= t.scale.z;

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