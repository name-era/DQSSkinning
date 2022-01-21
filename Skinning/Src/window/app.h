#pragma once
#define DEG2RAD 0.0174533f

#include "appBase.h"
#include "shader.h"
#include "attribute.h"
#include "IndexBuffer.h"
#include "texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

class App : public Application {
protected:
	float _rotation;
	Shader* _shader;
	Texture* _texture;
	Attribute<glm::vec3>* _vertexPositions;
	Attribute<glm::vec3>* _vertexNormals;
	Attribute<glm::vec2>* _vertexTexCoords;
	IndexBuffer* _indexBuffer;

public:
	
	App();
	
	/**
	* 初期化
	*/
	void Initialize();

	/**
	* パラメータの更新
	*/
	void Update(float deltaTime);

	/**
	* 描画
	*/
	void Render(float aspectRatio);

	/**
	* 終了時のインスタンス削除
	*/
	void Shutdown();
};