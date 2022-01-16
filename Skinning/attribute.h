#pragma once

#include "glm/glm.hpp"
#include "glad.h"

class Attribute {
private:
	uint32_t _handle;
	uint32_t _count;
	
	/**
	* コピーコンストラクタの禁止
	*/
	Attribute(const Attribute& other);
	
	/**
	* 代入演算子の禁止
	*/
	Attribute& operator=(const Attribute& other);

public:
	/**
	* コンストラクタ
	*/
	Attribute();


	/**
	* デストラクタ
	*/
	~Attribute();

	/**
	* Attribute変数の数を取得する
	*/
	uint32_t GetCount();

	/**
	* Attribute Buffer Objectを取得する
	*/
	uint32_t GetHandle();

	/**
	* 頂点データを送る
	*/
	uint32_t Set(const void* data, uint32_t arrayLength);

	/**
	* Attribute変数をセットする
	*/
	void BindAttribute(uint32_t slot, GLint size);

	/**
	* Attribute変数をセットする
	*/
	void UnBindAttribute(uint32_t slot);
};