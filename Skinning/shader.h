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

	//コピーコンストラクタ、代入演算子の禁止
	Shader(const Shader&);
	Shader& operator=(const Shader&);

	Shader();
	Shader(const std::string& vertex, const std::string& fragment);
	~Shader();

	/**
	* シェーダーファイルを読み込む
	*/
	std::vector<char> ReadFile(const std::string& filename);
	
	/**
	* 頂点シェーダーをコンパイルする
	*/
	uint32_t CompileVertexShader(const std::vector<char> vertex);
	
	/**
	* シェーダーをコンパイルする
	*/
	uint32_t CompileFragmentShader(const std::vector<char> fragment);
	
	/**
	* シェーダーをリンクする
	*/
	bool LinkShaders(uint32_t vertex, uint32_t fragment);
	
	/**
	* Attribute変数を取得する
	*/
	void PopulateAttributes();

	/**
	* Uniform変数を取得する
	*/
	void PopulateUniforms();

	/**
	* シェーダーを読み込む
	*/
	void Load(const std::string& vertex, const std::string& fragment);
	
	
	
	void Bind();
	void UnBind();
	uint32_t GetAttribute(const std::string& name);
	uint32_t GetUniform(const std::string& name);
	uint32_t GetHandle();


};