#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include <vector>

template<typename T>
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
	static void Set(uint32_t slot, T* inputArray, uint32_t arrayLength);

	/**
	* uniform変数をセットする
	*/
	static void Set(uint32_t slot, const T& value);
	


	static void Set(uint32_t slot, std::vector<T>& inputArray);
};