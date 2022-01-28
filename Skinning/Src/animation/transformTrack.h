#pragma once

#include "track.h"


class TransformTrack {
protected:
	uint32_t _id;
	VectorTrack _position;
	QartanionTrack _rotation;
	VectorTrack _scale;

public:
	TransformTrack();
	uint32_t GetId();
	VectorTrack& GetPositionTrack();
	VectorTrack& GetScaleTrack();
	VectorTrack& GetRotationTrack();
	bool IsValid();

	float GetStartTime();
	float GetEndTime();

};