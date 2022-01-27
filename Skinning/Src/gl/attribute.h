#pragma once
#include "glm/glm.hpp"
#include <vector>

template<typename T>
class Attribute {
protected:
	uint32_t _handle;
	uint32_t _count;
private:
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
	void Set(T* inputArray, uint32_t arrayLength);

	/**
	* ���_�f�[�^���Z�b�g����
	*/
	void Set(std::vector<T>& input);

	/**
	* Attribute pointer���Z�b�g����
	*/
	void SetAttributePointer(uint32_t slot);

	/**
	* Attribute�ϐ����Z�b�g����
	*/
	void BindTo(uint32_t slot);

	/**
	* Attribute�ϐ����Z�b�g����
	*/
	void UnBind(uint32_t slot);
};