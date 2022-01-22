#include "track.h"

template Track<float, 1>;
template Track<glm::vec3, 3>;
template Track<glm::quat, 4>;

template<typename T, uint32_t N>
void Track<T, N>::SetInterpolation(Interpolation interpolation) {
	_interpolation = interpolation;
}

template<typename T, uint32_t N>
void Track<T, N>::Resize(uint32_t size) {
	_frames.resize(size);
}

template<> float Track<float, 1>::Cast(float* value) {
	return value[0];
}

template<> glm::vec3 Track<glm::vec3, 3>::Cast(float* value) {
	return glm::vec3(value[0], value[1], value[2]);
}

template<> glm::quat Track<glm::quat, 4>::Cast(float* value) {
	glm::quat r = glm::quat(value[0], value[1], value[2], value[3]);
	return glm::normalize(r);
}

template<typename T, uint32_t N>
uint32_t Track<T, N>::GetFrameIndex(float time, bool looping) {
	uint32_t size = _frames.size();
	if (size <= 1) {
		return -1;
	}
	if (looping) {
		float startTime = _frames[0].time;
		float endTime = _frames[size - 1].time;
		float dulation = endTime - startTime;

		time = fmodf(time - startTime, endTime - startTime);
		if (time < 0.0f) {
			time += endTime - startTime;
		}
		time += startTime;
	}
	else {
		//1コマ目まで
		if (time <= _frames[0].time) {
			return 0;
		}
		//最後のコマ以降
		if (time >= _frames[size - 2].time) {
			return size - 2;
		}
	}

	for (uint32_t i = size - 1; i >= 0; i--) {
		//コマ打ちされている時間以降であればそのコマを返す
		if (time > _frames[i].time) {
			return i;
		}
	}
}

template<typename T, uint32_t N>
float Track<T, N>::AdjustTimeToFitTrack(float time, bool looping) {
	uint32_t size = _frames.size();
	if (size <= 1) {
		return 0.0f;
	}

	float startTime = _frames[0].time;
	float endTime = _frames[size - 1].time;
	float duration = endTime - startTime;
	if (duration <= 0.0f) {
		return 0.0f;
	}

	if (looping) {
		time = fmodf(time - startTime, endTime - startTime);
		if (time < 0.0f) {
			time += endTime - startTime;
		}
		time += startTime;
	}
	else {
		if (time <= _frames[0].time) {
			time = startTime;
		}
		if (time >= _frames[size - 1].time) {
			time = endTime;
		}
	}

	return time;
}

template<typename T, uint32_t N>
T Track<T, N>::GetConstantValue(float time, bool looping) {
	uint32_t frame = GetFrameIndex(time, looping);
	if (frame < 0 || frame >= _frames.size()) {
		return T();
	}
	return Cast(&_frames[frame].value[0]);
}

template<typename T, uint32_t N>
T Track<T, N>::GetLinearValue(float time, bool looping) {
	uint32_t thisFrame = GetFrameIndex(time, looping);
	if (thisFrame < 0 || thisFrame >= _frames.size()) {
		return T();
	}
	uint32_t nextFrame = thisFrame + 1;

	//経過時間
	float trackTime = AdjustTimeToFitTrack(time, looping);
	float frameDelta = _frames[nextFrame].time - _frames[thisFrame].time;
	if (frameDelta <= 0.0f) {
		return T();
	}

	//現在のフレームの開始時間からどれくらいの時間が進んでいるか
	float t = (trackTime - _frames[thisFrame].time) / frameDelta;

	T start = Cast(&_frames[thisFrame].value[0]);
	T end = Cast(&_frames[nextFrame].value[0]);

	return glm::mix(start, end, t);
}

template<typename T, uint32_t N>
T Track<T, N>::GetCubicValue(float time, bool looping) {
	uint32_t thisFrame = GetFrameIndex(time, looping);
	if (thisFrame < 0 || thisFrame >= _frames.size()) {
		return T();
	}
	uint32_t nextFrame = thisFrame + 1;

	//経過時間
	float trackTime = AdjustTimeToFitTrack(time, looping);
	float frameDelta = _frames[nextFrame].time - _frames[thisFrame].time;
	if (frameDelta <= 0.0f) {
		return T();
	}

	//現在のフレームの開始時間からどれくらいの時間が進んでいるか
	float t = (trackTime - _frames[thisFrame].time) / frameDelta;

	T point1 = Cast(_frames[thisFrame].value[0]);
	//傾き
	T slope1;
	memcpy(&slope1, _frames[thisFrame].out, N * sizeof(float));
	slope1 *= frameDelta;

	T point2 = Cast(_frames[nextFrame].value[0]);
	//傾き
	T slope2;
	memcpy(&slope2, _frames[nextFrame].in, N * sizeof(float));
	slope2 *= frameDelta;

	return glm::hermite(point1, slope1, point2, slope2, t);
}

template<typename T, uint32_t N>
T Track<T, N>::GetValue(float time, bool looping) {
	if (_interpolation == Interpolation::Constant) {
		return GetConstantValue(time, looping);
	}
	else if (_interpolation == Interpolation::Linear) {
		return GetLinearValue(time, looping);
	}
	else {
		return GetCubicValue(time, looping);
	}

}

template<typename T, uint32_t N>
Frame<N>& Track<T, N>::operator[](uint32_t index) {
	_frames[index];
}

template<typename T, uint32_t N>
Interpolation Track<T, N>::GetInterpolation() {
	return _interpolation;
}