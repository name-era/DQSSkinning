#pragma once

#include <vector>
#include "transform.h"

class Pose {
protected:
	std::vector<Transform>	_joints;
	std::vector<uint32_t> _parents;

public:
	/**
	* �R���X�g���N�^
	*/
	Pose();
	Pose(uint32_t numJoiints);

	/**
	* �W���C���g�̐��̕ύX
	*/
	void Resize(uint32_t size);

	/**
	* �R�s�[�R���X�g���N�^
	*/
	Pose(const Pose& p);

	/**
	* ������Z�q
	*/
	Pose& operator=(const Pose& p);

	/**
	* �T�C�Y���擾����
	*/
	uint32_t GetSize();

	/**
	* ���[�J���g�����X�t�H�[�����Z�b�g����
	*/
	void SetLocalTransform(uint32_t index, const Transform& transform);

	/**
	* ���[�J���g�����X�t�H�[�����擾����
	*/
	Transform GetLocalTransform(uint32_t index);
	
	/**
	* �O���[�o���g�����X�t�H�[�����擾����
	*/
	Transform GetGlobalTransform(uint32_t index);

	Transform operator[](uint32_t index);

	void GetMatrixPalette(std::vector<glm::mat4>& out);

	/**
	* �e���Z�b�g����
	*/
	void SetParent(uint32_t index, int parent);

	/**
	* �e���擾����
	*/
	int GetParent(uint32_t index);

	bool operator==(const Pose& other);
	bool operator!=(const Pose& other);
};