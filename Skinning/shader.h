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

	/**
	* コピーコンストラクタの禁止
	*/
	Shader(const Shader&);

	/**
	* 代入演算子の禁止
	*/
	Shader& operator=(const Shader&);

	/**
	* コンストラクタ
	*/
	Shader();
	Shader(const std::string& vertex, const std::string& fragment);
	
	/**
	* デストラクタ
	*/
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
	
	/**
	* シェーダーをバインドする
	*/
	void Bind();

	/**
	* シェーダーをアンバインドする
	*/
	void UnBind();

	/**
	* シェーダーオブジェクトを取得する
	*/
	uint32_t GetHandle();

	/**
	* Attribute Indexを取得する
	*/
	uint32_t GetAttributeIndex(const std::string& name);

	/**
	* Uniform Indexを取得する
	*/
	uint32_t GetUniformIndex(const std::string& name);
};