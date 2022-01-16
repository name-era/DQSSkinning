#pragma once

#include <map>
#include <string>
#include <fstream>
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

	std::vector<char> ReadFile(const std::string& filename);
	uint32_t CompileVertexShader(const std::string& vertex);
	uint32_t CompileFragmentShader(const std::string& fragment);
	bool LinkShaders(uint32_t vertex, uint32_t fragment);
	void PopulateAttributes();
	void PopulateUniforms();

	void Load(const std::string& vertex, const std::string& fragment);
	void Bind();
	void UnBind();
	uint32_t GetAttribute(const std::string& name);
	uint32_t GetUniform(const std::string& name);
	uint32_t GetHandle();


};