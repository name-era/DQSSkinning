#pragma once
#include <stdint.h>

class Texture {
protected:
	uint32_t _width;
	uint32_t _height;
	uint32_t _channels;
	uint32_t _handle;

private:
	/**
	* コピーコンストラクタの禁止
	*/
	Texture(const Texture& other);

	/**
	* 代入演算子の禁止
	*/
	Texture& operator=(const Texture& other);

public:

	/**
	* コンストラクタ
	*/
	Texture();



	/**
	* デストラクタ
	*/
	~Texture();

	/**
	* テクスチャをロードする
	*/
	void Load(const char* path);

	/**
	* コンストラクタ
	*/
	Texture(const char* path);

	/**
	* テクスチャのインデックスをテクスチャのユニフォーム変数に設定する
	*/
	void Set(uint32_t uniformIndex, uint32_t textureIndex);

	/**
	* テクスチャをアンバインドする
	*/
	void UnSet( uint32_t textureIndex);

	/**
	*テクスチャオブジェクトのIDを取得する
	*/
	uint32_t GetHandle();
};