#pragma once
#include "interpolation.h"
#include "frame.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_interpolation.hpp>
#include <vector>

template<typename T, uint32_t N>
class Track {
protected:
	Interpolation _interpolation;
	std::vector<Frame<N>> _frames;

public:
	Track();
	~Track();

	void SetInterpolation(Interpolation interpolation);
	void Resize(uint32_t size);

	uint32_t FrameIndex(float time, bool looping);
	T GetConstantPos(float time, bool looping);
	/**
	* ���Ԃ��g���b�N�͈̔͂ɍ��킹��
	*/
	float AdjustTimeToFitTrack(float time, bool looping);

	/**
	* ���`��Ԃ����Ƃ��̒l�����߂�
	*/
	T GetLinearPos(float time, bool looping);
	T GetPos(float time, bool looping);

	/**
	* �t���[����ǉ�����
	*/
	Frame<N>& operator[](uint32_t index);
};

typedef Track<float, 1> ScalarTrack;
typedef Track<glm::vec3, 3> VectorTrack;
typedef Track<glm::quat, 4> QartanionTrack;