#pragma once
#include "glm/glm.hpp"
#include "glad.h"

class Uniform {

private:
	/**
	* コピーコンストラクタの禁止
	*/
	Uniform(const Uniform&);

	/**
	* 代入演算子の禁止
	*/
	Uniform& operator=(const Uniform&);

public:

	/**
	* コンストラクタ
	*/
	Uniform() {};

	/**
	* デストラクタ
	*/
	~Uniform() {};

	/**
	* uniform変数をセットする
	*/
	static void Set(uint32_t slot, const void* data, GLsizei arrayLength);
};