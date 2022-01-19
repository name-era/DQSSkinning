#pragma once
#include "glm/glm.hpp"
#include <vector>

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
	* Index�̃f�[�^�𑗂�
	*/
	void Set(const void* data, uint32_t arrayLength);

	/**
	* Index�̃f�[�^���Z�b�g����
	*/
	void Set(std::vector<uint32_t>& input);

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