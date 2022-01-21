#pragma once
#include "interpolation.h"
#include "frame.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <vector>

template<typename T, uint32_t N>
class Track {
protected:
	Interpolation _interpolation;
	std::vector<Frame<N>> _frames;

public:
	Track();
	~Track();

	void SetInterpolation(Interpolation interpolation);
	void Resize(uint32_t size);

	/**
	* ƒtƒŒ[ƒ€‚ğ’Ç‰Á‚·‚é
	*/
	Frame<N>& operator[](uint32_t index);
};

typedef Track<float, 1> ScalarTrack;
typedef Track<glm::vec3, 3> VectorTrack;
typedef Track<glm::quat, 4> QartanionTrack;