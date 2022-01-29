#pragma once
#include <iostream>
#include "transformTrack.h"
#include "pose.h"

class AnimationClip {
protected:
	std::vector<TransformTrack> _tracks;
	std::string _name;
	float _startTime;
	float _endTime;
	bool _isLoop;

public:
	void SetName(const std::string& inNewName);
	TransformTrack& operator[](uint32_t index);
	void RecalculateDuration();
	std::string& GetName();

	float AdjustTime(float inTime);
	float Animate(Pose& outPose, float inTime);
};