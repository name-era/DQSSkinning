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