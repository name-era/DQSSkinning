#pragma once
#include "glm/glm.hpp"
#include "glad.h"

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
	static void Set(uint32_t slot, const void* data, GLsizei arrayLength);
};