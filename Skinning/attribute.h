#pragma once

#include "glm/glm.hpp"
#include "glad.h"

class Attribute {
private:
	uint32_t _handle;
	uint32_t _count;
	
	/**
	* �R�s�[�R���X�g���N�^�̋֎~
	*/
	Attribute(const Attribute& other);
	
	/**
	* ������Z�q�̋֎~
	*/
	Attribute& operator=(const Attribute& other);

public:
	/**
	* �R���X�g���N�^
	*/
	Attribute();


	/**
	* �f�X�g���N�^
	*/
	~Attribute();

	/**
	* Attribute�ϐ��̐����擾����
	*/
	uint32_t GetCount();

	/**
	* Attribute Buffer Object���擾����
	*/
	uint32_t GetHandle();

	/**
	* ���_�f�[�^�𑗂�
	*/
	uint32_t Set(const void* data, uint32_t arrayLength);

	/**
	* Attribute�ϐ����Z�b�g����
	*/
	void BindAttribute(uint32_t slot, GLint size);

	/**
	* Attribute�ϐ����Z�b�g����
	*/
	void UnBindAttribute(uint32_t slot);
};