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
	* ������
	*/
	void Initialize();

	/**
	* �p�����[�^�̍X�V
	*/
	void Update(float deltaTime);

	/**
	* �`��
	*/
	void Render(float aspectRatio);

	/**
	* �I�����̃C���X�^���X�폜
	*/
	void Shutdown();
};