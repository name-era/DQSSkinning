#pragma once
#include "glm/glm.hpp"
#include <vector>

template<typename T>
class Attribute {
protected:
	uint32_t _handle;
	uint32_t _count;
private:
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
	void Set(T* inputArray, uint32_t arrayLength);

	/**
	* 頂点データをセットする
	*/
	void Set(std::vector<T>& input);

	/**
	* Attribute pointerをセットする
	*/
	void SetAttributePointer(uint32_t slot);

	/**
	* Attribute変数をセットする
	*/
	void BindTo(uint32_t slot);

	/**
	* Attribute変数をセットする
	*/
	void UnBind(uint32_t slot);
};