#pragma once
#include "interpolation.h"
#include "frame.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/spline.hpp>
#include <vector>

template<typename T, uint32_t N>
class Track {
protected:
	Interpolation _interpolation;
	std::vector<Frame<N>> _frames;

protected:

	T Cast(float* value);

	/**
	* �t���[���̃C���f�b�N�X���擾����
	*/
	uint32_t GetFrameIndex(float time, bool looping);

	/**
	* ���Ԃ��g���b�N�͈̔͂ɍ��킹��
	*/
	float AdjustTimeToFitTrack(float time, bool looping);

	/**
	* ��Ԃ��Ȃ��Ƃ��̒l�����߂�
	*/
	T GetConstantValue(float time, bool looping);

	/**
	* ���`��Ԃ����Ƃ��̒l�����߂�
	*/
	T GetLinearValue(float time, bool looping);


	/**
	* �L���[�r�b�N�G���~�[�g��ԗp�֐�
	*/
	T Hermite(float t, const T& p1, const T& s1, const T& _p2, const T& s2);

	/**
	* �L���[�r�b�N��Ԃ����Ƃ��̒l�����߂�
	*/
	T GetCubicValue(float time, bool looping);

public:

	/**
	* �R���X�g���N�^
	*/
	Track() {};

	/**
	* �f�X�g���N�^
	*/
	~Track() {};

	/**
	* ��Ԃ̎�ނ��Z�b�g����
	*/
	void SetInterpolation(Interpolation interpolation);

	/**
	* �t���[���̒������Z�b�g����
	*/
	void Resize(uint32_t size);
	
	/**
	* �l�����߂�
	*/
	T GetValue(float time, bool looping);

	/**
	* �t���[����ǉ�����
	*/
	Frame<N>& operator[](uint32_t index);

	Interpolation GetInterpolation();

};

typedef Track<float, 1> ScalarTrack;
typedef Track<glm::vec3, 3> VectorTrack;
typedef Track<glm::quat, 4> QartanionTrack;