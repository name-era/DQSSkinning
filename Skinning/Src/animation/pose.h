#pragma once

#include <vector>
#include "transform.h"

class Pose {
protected:
	std::vector<Transform>	_joints;
	std::vector<uint32_t> _parents;

public:
	/**
	* コンストラクタ
	*/
	Pose();
	Pose(uint32_t numJoiints);

	/**
	* ジョイントの数の変更
	*/
	void Resize(uint32_t size);

	/**
	* コピーコンストラクタ
	*/
	Pose(const Pose& p);

	/**
	* 代入演算子
	*/
	Pose& operator=(const Pose& p);

	/**
	* サイズを取得する
	*/
	uint32_t GetSize();

	/**
	* ローカルトランスフォームをセットする
	*/
	void SetLocalTransform(uint32_t index, const Transform& transform);

	/**
	* ローカルトランスフォームを取得する
	*/
	Transform GetLocalTransform(uint32_t index);
	
	/**
	* グローバルトランスフォームを取得する
	*/
	Transform GetGlobalTransform(uint32_t index);

	Transform operator[](uint32_t index);

	void GetMatrixPalette(std::vector<glm::mat4>& out);

	/**
	* 親をセットする
	*/
	void SetParent(uint32_t index, int parent);

	/**
	* 親を取得する
	*/
	int GetParent(uint32_t index);

	bool operator==(const Pose& other);
	bool operator!=(const Pose& other);
};