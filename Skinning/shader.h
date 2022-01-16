#pragma once

#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

class Shader {
private:
	uint32_t _handle;
	std::map<std::string, uint32_t> _attributes;
	std::map < std::string, uint32_t> _uniforms;

	//�R�s�[�R���X�g���N�^�A������Z�q�̋֎~
	Shader(const Shader&);
	Shader& operator=(const Shader&);

	Shader();
	Shader(const std::string& vertex, const std::string& fragment);
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
	
	
	
	void Bind();
	void UnBind();
	uint32_t GetAttribute(const std::string& name);
	uint32_t GetUniform(const std::string& name);
	uint32_t GetHandle();


};