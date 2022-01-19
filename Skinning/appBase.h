#pragma once

class Application{
private:
	Application(const Application&);
	Application& operator=(const Application&);
public:

	/**
	* �R���X�g���N�^
	*/
	inline Application() {};

	/**
	* �f�X�g���N�^
	*/
	inline virtual ~Application() {};

	/**
	* ������
	*/
	inline virtual void Initialize() {};

	/**
	* �X�V
	*/
	inline virtual void Update(float deltaTime) {};

	/**
	* �`��
	*/
	inline virtual void Render(float aspectRatio) {};
	
	/**
	* �I����
	*/
	inline virtual void Shutdown() {};
};