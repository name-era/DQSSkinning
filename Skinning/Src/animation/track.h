#pragma once
#include "interpolation.h"
#include "frame.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/spline.hpp>
#include <vector>

template<typename T, uint32_t N>
class Track {
protected:
	Interpolation _interpolation;
	std::vector<Frame<N>> _frames;

public:

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
	* キュービック補間したときの値を求める
	*/
	T GetCubicValue(float time, bool looping);

protected:

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
	* フレームの長さをセットする
	*/
	void Resize(uint32_t size);
	
	/**
	* 値を求める
	*/
	T GetValue(float time, bool looping);

	/**
	* フレームを追加する
	*/
	Frame<N>& operator[](uint32_t index);
};

typedef Track<float, 1> ScalarTrack;
typedef Track<glm::vec3, 3> VectorTrack;
typedef Track<glm::quat, 4> QartanionTrack;