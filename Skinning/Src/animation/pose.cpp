#include "pose.h"

Pose::Pose() {};

void Pose::Resize(uint32_t size) {
	_parents.resize(size);
	_joints.resize(size);
}

Pose::Pose(uint32_t numJoints) {
	Resize(numJoints);
}

Pose::Pose(const Pose& p) {
	*this = p;
}

Pose& Pose::operator=(const Pose& p) {
	if (&p == this) {
		return *this;
	}
	//サイズを揃える
	if (_parents.size() != p._parents.size()) {
		_parents.resize(p._parents.size());
	}
	if (_joints.size() != p._joints.size()) {
		_joints.resize(p._joints.size());
	}
	//中身をコピーする
	if (_parents.size() != 0) {
		memcpy(&_parents[0], &p._parents[0], sizeof(uint32_t) * _parents.size());
	}
	if (_joints.size() != 0) {
		memcpy(&_joints[0], &p._joints[0], sizeof(Transform) * _joints.size());
	}

	return *this;
}

uint32_t Pose::GetSize() {
	return _joints.size();
}

void Pose::SetLocalTransform(uint32_t index, const Transform& transform) {
	_joints[index] = transform;
}

Transform Pose::GetLocalTransform(uint32_t index) {
	return _joints[index];
}

Transform Pose::GetGlobalTransform(uint32_t index) {
	Transform result = _joints[index];
	//親まで遡って求める
	for (uint32_t parent = _parents[index]; parent >= 0; parent = _parents[parent]) {
		result = Combine(_joints[parent], result);

	}
	return result;
}

Transform Pose::operator[](uint32_t index) {
	return GetGlobalTransform(index);
}

void Pose::GetMatrixPalette(std::vector<glm::mat4>& out) {
	uint32_t size = GetSize();
	if (out.size() != size) {
		out.resize(size);
	}
	for(uint32_t i = 0; i < size; i++) {
		Transform t = GetGlobalTransform(i);
		out[i] = TransformToMat4(t);
	}
}

void Pose::SetParent(uint32_t index, uint32_t parent) {
	_parents[index] = parent;
}

uint32_t Pose::GetParent(uint32_t index) {
	return _parents[index];
}

bool Pose::operator==(const Pose& other) {

	if (_joints.size() != other._joints.size()) {
		return false;
	}
	if (_parents.size() != other._parents.size()) {
		return false;
	}

	uint32_t size = _joints.size();
	for (uint32_t i = 0; i < size; i++) {

		Transform thisLocal = _joints[i];
		Transform otherLocal = other._joints[i];
		uint32_t thisParent = _parents[i];
		uint32_t otherParent = other._parents[i];

		if (thisParent != otherParent) {
			return false;
		}
		if (thisLocal != otherLocal) {
			return false;
		}
		return true;
	}
}

bool Pose::operator!=(const Pose& other) {
	return !(*this == other);
}