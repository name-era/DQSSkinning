#pragma once

#include "glm/glm.hpp"
#include "glad.h"

class IndexBuffer {

private:
	/**
	* コピーコンストラクタの禁止
	*/
	IndexBuffer(const IndexBuffer& other);

	/**
	* 代入演算子の禁止
	*/
	IndexBuffer& operator=(const IndexBuffer& other);

public:
	/**
	* コンストラクタ
	*/
	IndexBuffer();

	/**
	* デストラクタ
	*/
	~IndexBuffer();

	/**
	* Index Bufferの数を取得する
	*/
	void SetIndex(const void* data, uint32_t arrayLength);

	/**
	* Index Bufferの数を取得する
	*/
	uint32_t GetCount();

	/**
	* Index Bufferのハンドルを取得する
	*/
	uint32_t GetHandle();



	uint32_t _handle;
	uint32_t _count;
};