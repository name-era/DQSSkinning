#pragma once

class Application{
private:
	Application(const Application&);
	Application& operator=(const Application&);
public:

	/**
	* コンストラクタ
	*/
	inline Application() {};

	/**
	* デストラクタ
	*/
	inline virtual ~Application() {};

	/**
	* 初期化
	*/
	inline virtual void Initialize() {};

	/**
	* 更新
	*/
	inline virtual void Update(float deltaTime) {};

	/**
	* 描画
	*/
	inline virtual void Render(float aspectRatio) {};
	
	/**
	* 終了時
	*/
	inline virtual void Shutdown() {};
};