#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include <vector>

template<typename T>
class Uniform {

private:
	/**
	* �R�s�[�R���X�g���N�^�̋֎~
	*/
	Uniform(const Uniform&);

	/**
	* ������Z�q�̋֎~
	*/
	Uniform& operator=(const Uniform&);

public:

	/**
	* �R���X�g���N�^
	*/
	Uniform() {};

	/**
	* �f�X�g���N�^
	*/
	~Uniform() {};

	/**
	* uniform�ϐ����Z�b�g����
	*/
	static void Set(uint32_t slot, T* inputArray, uint32_t arrayLength);

	/**
	* uniform�ϐ����Z�b�g����
	*/
	static void Set(uint32_t slot, const T& value);
	


	static void Set(uint32_t slot, std::vector<T>& inputArray);
};