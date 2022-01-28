#include "transformTrack.h"

uint32_t TransformTrack::GetId() {
	return _id;
}

VectorTrack& TransformTrack::GetPositionTrack() {
	return _position;
}

VectorTrack& TransformTrack::GetScaleTrack() {
	return _scale;
}

VectorTrack& TransformTrack::GetRotationTrack() {
	return _rotation;
}

bool TransformTrack::IsValid() {
	return _position.GetSize() > 1 || _rotation.GetSize() > 1 || _scale.GetSize() > 1;
}

float TransformTrack::GetStartTime() {
	float result = 0.0f;
	bool isSet = false;

	//position, rotation, scale�łǂꂪ��ԊJ�n����̂�������
	if (_position.GetSize() > 1) {
		result = _position.GetStartTime();
		isSet = true;
	}
	if (_rotation.GetSize() > 1) {
		float rotationStart = _rotation.GetStartTime();
		if (rotationStart < result || !isSet) {
			result = rotationStart;
			isSet = true;
		}
	}
	if (_scale.GetSize() > 1) {
		float scaleStart = _scale.GetStartTime();
		if (scaleStart < result || !isSet) {
			result = scaleStart;
			isSet = true;
		}
	}

	return result;
}


float TransformTrack::GetEndTime() {
	float result = 0.0f;
	bool isSet = false;

	//position, rotation, scale�łǂꂪ��ԏI������̂��x����
	if (_position.GetSize() > 1) {
		result = _position.GetEndTime();
		isSet = true;
	}
	if (_rotation.GetSize() > 1) {
		float rotationEnd = _rotation.GetEndTime();
		if (rotationEnd > result || !isSet) {
			result = rotationEnd;
			isSet = true;
		}
	}
	if (_scale.GetSize() > 1) {
		float scaleEnd = _scale.GetEndTime();
		if (scaleEnd > result || !isSet) {
			result = scaleEnd;
			isSet = true;
		}
	}

	return result;
}