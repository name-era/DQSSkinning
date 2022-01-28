#include "animationClip.h"

void AnimationClip::SetName(const std::string& inNewName) {
	_name = inNewName;
}

TransformTrack& AnimationClip::operator[](uint32_t joint) {
	uint32_t size = (uint32_t)_tracks.size();
	for (uint32_t i = 0; i < size; i++) {
		if (_tracks[i].GetId() == joint) {
			return _tracks[i];
		}
	}
	_tracks.push_back(TransformTrack());
	_tracks[_tracks.size() - 1].SetId(joint);
	return _tracks[_tracks.size() - 1];
}


void AnimationClip::RecalculateDuration() {
	_startTime = 0.0f;
	_endTime = 0.0f;
	bool startSet = false;
	bool endSet = false;
	unsigned int tracksSize = (unsigned int)_tracks.size();

	for (unsigned int i = 0; i < tracksSize; ++i) {
		if (_tracks[i].IsValid()) {
			float trackStartTime = _tracks[i].GetStartTime();
			float trackEndTime = _tracks[i].GetEndTime();

			if (trackStartTime < _startTime || !startSet) {
				_startTime = trackStartTime;
				startSet = true;
			}

			if (trackEndTime > _endTime || !endSet) {
				_endTime = trackEndTime;
				endSet = true;
			}
		}
	}
}

std::string& AnimationClip::GetName() {
	return _name;
}

float AnimationClip::AdjustTime(float inTime) {
	if (_isLoop) {
		float duration = _endTime - _startTime;
		if (duration <= 0) {
			return 0.0f;
		}
		inTime = fmodf(inTime - _startTime, _endTime - _startTime);
		if (inTime < 0.0f) {
			inTime += _endTime - _startTime;
		}
		inTime = inTime + _startTime;
	}
	else {
		if (inTime < _startTime) {
			inTime = _startTime;
		}
		if (inTime > _endTime) {
			inTime = _endTime;
		}
	}
	return inTime;
}

float AnimationClip::Sample(Pose& outPose, float time) {
	
	if ((_endTime-_startTime) == 0.0f) {
		return 0.0f;
	}
	time = AdjustTime(time);

	uint32_t size = (uint32_t)_tracks.size();
	for (unsigned int i = 0; i < size; ++i) {
		unsigned int joint = _tracks[i].GetId();
		Transform local = outPose.GetLocalTransform(joint);
		Transform animated = _tracks[i].GetValue(local, time, _isLoop);
		outPose.SetLocalTransform(joint, animated);
	}
	return time;
}