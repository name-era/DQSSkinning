#pragma once

#include "track.h"
#include "transform.h"

class TransformTrack {
protected:
	uint32_t _id;
	VectorTrack _position;
	QartanionTrack _rotation;
	VectorTrack _scale;

public:
	TransformTrack();
	void SetId(uint32_t id);
	uint32_t GetId();
	VectorTrack& GetPositionTrack();
	VectorTrack& GetScaleTrack();
	QartanionTrack& GetRotationTrack();
	bool IsValid();

	float GetStartTime();
	float GetEndTime();
	Transform GetValue(const Transform& ref, float time, bool looping);
};