#include "animationClip.h"

void AnimationClip::SetName(const std::string& inNewName) {
	_name = inNewName;
}

TransformTrack& AnimationClip::operator[](uint32_t joint) {
	uint32_t size = _tracks.size();
	for (uint32_t i = 0; i < size; i++) {
		if (_tracks[i].GetId() == joint) {
			return _tracks[i];
		}
	}
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
	if (mLooping) {
		float duration = mEndTime - mStartTime;
		if (duration <= 0) {
			return 0.0f;
		}
		inTime = fmodf(inTime - mStartTime, mEndTime - mStartTime);
		if (inTime < 0.0f) {
			inTime += mEndTime - mStartTime;
		}
		inTime = inTime + mStartTime;
	}
	else {
		if (inTime < mStartTime) {
			inTime = mStartTime;
		}
		if (inTime > mEndTime) {
			inTime = mEndTime;
		}
	}
	return inTime;
}

float AnimationClip::Sample(Pose& outPose, float time) {
	
	if ((_endTime-_startTime) == 0.0f) {
		return 0.0f;
	}
	time = AdjustTimeToFitRange(time);

	unsigned int size = mTracks.size();
	for (unsigned int i = 0; i < size; ++i) {
		unsigned int joint = mTracks[i].GetId();
		Transform local = outPose.GetLocalTransform(joint);
		Transform animated = mTracks[i].Sample(local, time, mLooping);
		outPose.SetLocalTransform(joint, animated);
	}
	return time;
}