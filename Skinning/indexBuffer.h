#pragma once

#include "glm/glm.hpp"
#include "glad.h"

class IndexBuffer {

private:
	/**
	* �R�s�[�R���X�g���N�^�̋֎~
	*/
	IndexBuffer(const IndexBuffer& other);

	/**
	* ������Z�q�̋֎~
	*/
	IndexBuffer& operator=(const IndexBuffer& other);

public:
	/**
	* �R���X�g���N�^
	*/
	IndexBuffer();

	/**
	* �f�X�g���N�^
	*/
	~IndexBuffer();

	/**
	* Index Buffer�̐����擾����
	*/
	void SetIndex(const void* data, uint32_t arrayLength);

	/**
	* Index Buffer�̐����擾����
	*/
	uint32_t GetCount();

	/**
	* Index Buffer�̃n���h�����擾����
	*/
	uint32_t GetHandle();



	uint32_t _handle;
	uint32_t _count;
};