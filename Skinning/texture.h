#pragma once
#include "glad.h"
#include <stdint.h>

class Texture {
private:
	uint32_t _width;
	uint32_t _height;
	uint32_t _channels;
	GLuint _handle;

	/**
	* �R�s�[�R���X�g���N�^�̋֎~
	*/
	Texture(const Texture& other);

	/**
	* ������Z�q�̋֎~
	*/
	Texture& operator=(const Texture& other);

public:

	/**
	* �R���X�g���N�^
	*/
	Texture();



	/**
	* �f�X�g���N�^
	*/
	~Texture();

	/**
	* �e�N�X�`�������[�h����
	*/
	void Load(const char* path);

	/**
	* �R���X�g���N�^
	*/
	Texture(const char* path);

	/**
	* �e�N�X�`���̃C���f�b�N�X���e�N�X�`���̃��j�t�H�[���ϐ��ɐݒ肷��
	*/
	void Set(uint32_t uniformIndex, uint32_t textureIndex);

	/**
	* �e�N�X�`���̃��j�t�H�[���ϐ�������������
	*/
	void UnSet( uint32_t textureIndex);

	/**
	*�e�N�X�`���I�u�W�F�N�g��ID���擾����
	*/
	uint32_t GetHandle();
};