#pragma once
#include "interpolation.h"
#include "frame.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/spline.hpp>
#include <vector>

template<typename T, uint32_t N>
class Track {
protected:
	Interpolation _interpolation;
	std::vector<Frame<N>> _frames;

protected:

	T Cast(float* value);

	/**
	* フレームのインデックスを取得する
	*/
	uint32_t GetFrameIndex(float time, bool looping);

	/**
	* 時間をトラックの範囲に合わせる
	*/
	float AdjustTimeToFitTrack(float time, bool looping);

	/**
	* 補間しないときの値を求める
	*/
	T GetConstantValue(float time, bool looping);

	/**
	* 線形補間したときの値を求める
	*/
	T GetLinearValue(float time, bool looping);


	/**
	* キュービックエルミート補間用関数
	*/
	T Hermite(float t, const T& p1, const T& s1, const T& _p2, const T& s2);

	/**
	* キュービック補間したときの値を求める
	*/
	T GetCubicValue(float time, bool looping);

public:

	/**
	* コンストラクタ
	*/
	Track() {};

	/**
	* デストラクタ
	*/
	~Track() {};

	/**
	* 補間の種類をセットする
	*/
	void SetInterpolation(Interpolation interpolation);

	/**
	* フレームサイズをセットする
	*/
	void Resize(uint32_t size);
	
	/**
	* フレームサイズを取得する
	*/
	uint32_t GetSize();

	/**
	* 値を求める
	*/
	T GetValue(float time, bool looping);

	/**
	* フレームを追加する
	*/
	Frame<N>& operator[](uint32_t index);

	Interpolation GetInterpolation();

};

typedef Track<float, 1> ScalarTrack;
typedef Track<glm::vec3, 3> VectorTrack;
typedef Track<glm::quat, 4> QartanionTrack;