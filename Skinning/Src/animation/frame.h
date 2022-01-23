#pragma once
#include <stdint.h>

template<uint32_t N>

class Frame {
public:
	float value[N];
	float in[N];
	float out[N];
	float time;
};

typedef Frame<1> ScalarFrame;
typedef Frame<3> VectorFrame;
typedef Frame<4> QuartanionFrame;