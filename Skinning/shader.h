#pragma once

#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "glad.h"

class Shader {
private:
	uint32_t _handle;
	std::map<std::string, uint32_t> _attributes;
	std::map < std::string, uint32_t> _uniforms;

	/**
	* �R�s�[�R���X�g���N�^�̋֎~
	*/
	Shader(const Shader&);

	/**
	* ������Z�q�̋֎~
	*/
	Shader& operator=(const Shader&);

public:
	/**
	* �R���X�g���N�^
	*/
	Shader();
	Shader(const std::string& vertex, const std::string& fragment);
	
	/**
	* �f�X�g���N�^
	*/
	~Shader();


	/**
	* �V�F�[�_�[�t�@�C����ǂݍ���
	*/
	std::vector<char> ReadFile(const std::string& filename);
	
	/**
	* ���_�V�F�[�_�[���R���p�C������
	*/
	uint32_t CompileVertexShader(const std::vector<char> vertex);
	
	/**
	* �V�F�[�_�[���R���p�C������
	*/
	uint32_t CompileFragmentShader(const std::vector<char> fragment);
	
	/**
	* �V�F�[�_�[�������N����
	*/
	bool LinkShaders(uint32_t vertex, uint32_t fragment);
	
	/**
	* Attribute�ϐ����擾����
	*/
	void PopulateAttributes();

	/**
	* Uniform�ϐ����擾����
	*/
	void PopulateUniforms();

	/**
	* �V�F�[�_�[��ǂݍ���
	*/
	void Load(const std::string& vertex, const std::string& fragment);
	
	/**
	* �V�F�[�_�[���o�C���h����
	*/
	void Bind();

	/**
	* �V�F�[�_�[���A���o�C���h����
	*/
	void UnBind();

	/**
	* �V�F�[�_�[�I�u�W�F�N�g���擾����
	*/
	uint32_t GetHandle();

	/**
	* Attribute Index���擾����
	*/
	uint32_t GetAttributeIndex(const std::string& name);

	/**
	* Uniform Index���擾����
	*/
	uint32_t GetUniformIndex(const std::string& name);
};