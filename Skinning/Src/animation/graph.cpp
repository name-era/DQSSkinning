#include "graph.h"
#include <cstdarg>

ScalarTrack Graph::MakeScalarTrack(Interpolation interp, uint32_t numFrames, ...) {
	ScalarTrack result;
	result.SetInterpolation(interp);
	result.Resize(numFrames);

	va_list args;
	va_start(args, numFrames);

	//引数の数分追加する
	for (uint32_t i = 0; i < numFrames; i++) {
		result[i] = va_arg(args, ScalarFrame);
	}

	va_end(args);
	return result;
}

ScalarFrame Graph::MakeFrame(float time, float in, float value, float out) {
	ScalarFrame result;
	result.time = time;
	result.in[0] = in;
	result.value[0] = value;
	result.out[0] = out;
	return result;
}

ScalarFrame Graph::MakeFrame(float time, float value) {
	return MakeFrame(time, 0.0f, value, 0.0f);
}

VectorFrame Graph::MakeFrame(float time, const glm::vec3& in, const glm::vec3& value, const glm::vec3& out) {
	VectorFrame result;
	result.time = time;
	result.in[0] = in.x;
	result.in[1] = in.y;
	result.in[2] = in.z;
	result.value[0] = value.x;
	result.value[1] = value.y;
	result.value[2] = value.z;
	result.out[0] = out.x;
	result.out[1] = out.y;
	result.out[2] = out.z;
	return result;
}

VectorFrame Graph::MakeFrame(float time, const glm::vec3& value) {
	return MakeFrame(time, glm::vec3(), value, glm::vec3());
}

QuartanionFrame Graph::MakeFrame(float time, const glm::quat& in, const glm::quat& out, const glm::quat& value) {
	QuartanionFrame result;
	
	result.time = time;
	result.in[0] = in.x;
	result.in[0] = in.y;
	result.in[0] = in.z;
	result.in[0] = in.w;
	result.value[0] = value.x;
	result.value[1] = value.y;
	result.value[2] = value.z;
	result.value[3] = value.w;
	result.out[0] = out.x;
	result.out[1] = out.y;
	result.out[2] = out.z;
	result.out[3] = out.w;
	return result;

}

QuartanionFrame Graph::MakeFrame(float time, const glm::quat& value) {
	return MakeFrame(time, glm::quat(0, 0, 0, 0), value, glm::quat(0, 0, 0, 0));
}


void Graph::Initialize() {
	
	//line
	_scalarTracks.push_back(MakeScalarTrack(Interpolation::Linear, 2, MakeFrame(0.0f, 0.0f), MakeFrame(1.0f, 1.0f)));
	_scalarTracksLooping.push_back(false);

	_scalarTracks.push_back(MakeScalarTrack(Interpolation::Linear, 2, MakeFrame(0.0f, 0.0f), MakeFrame(0.5f, 1.0f)));
	_scalarTracksLooping.push_back(false);

	_scalarTracks.push_back(MakeScalarTrack(Interpolation::Linear, 3, MakeFrame(0.25f, 0.0f), MakeFrame(0.5f, 1.0f), MakeFrame(0.75f, 0.0f)));
	_scalarTracksLooping.push_back(true);

	_scalarTracks.push_back(MakeScalarTrack(Interpolation::Linear, 3, MakeFrame(0.25f, 0.0f), MakeFrame(0.5f, 1.0f), MakeFrame(0.75f, 0.0f)));
	_scalarTracksLooping.push_back(false);

	//mountain loop
	ScalarTrack stepTrack;
	stepTrack.Resize(11);
	stepTrack.SetInterpolation(Interpolation::Constant);
	for (uint32_t i = 0; i < 11; i++) {
		float time = (float)i / 10.0f * 0.5f + 0.25f;
		stepTrack[i] = MakeFrame(time, (i % 2 == 0.0f) ? 0.0f : 1.0f);
	}

	_scalarTracks.push_back(stepTrack);
	_scalarTracksLooping.push_back(true);

	_scalarTracks.push_back(stepTrack);
	_scalarTracksLooping.push_back(false);

	_scalarTracks.push_back(MakeScalarTrack(Interpolation::Cubic, 2, MakeFrame(0.25f, 0.0f, 0.0f, 0.0f), MakeFrame(0.75f, 0.0f, 1.0f, 0.0f)));
	_scalarTracksLooping.push_back(false);

	_scalarTracks.push_back(MakeScalarTrack(Interpolation::Cubic, 3, MakeFrame(0.25f, 0.0f, 0.0f, 0.0f), MakeFrame(0.5f, 0.0f, 1.0f, 0.0f), MakeFrame(0.75f, 0.0f, 0.0f, 0.0f)));
	_scalarTracksLooping.push_back(true);

	_scalarTracks.push_back(MakeScalarTrack(Interpolation::Cubic, 5, MakeFrame(0.25f, 0.0f, 0.0f, 0.0f), MakeFrame(0.375f, 0.0f, 0.5f, 0.0f), MakeFrame(0.5f, 0.0f, 1.0f, 0.0f), MakeFrame(0.875f, 0.0f, 0.5f, 0.0f), MakeFrame(1.0f, 0.0f, 0.0f, 0.0f)));
	_scalarTracksLooping.push_back(true);

	_scalarTracks.push_back(MakeScalarTrack(Interpolation::Cubic, 5, MakeFrame(0.25f, 0.0f, 0.0f, 0.0f), MakeFrame(0.375f, -10.0f, 0.5f, -10.0f), MakeFrame(0.5f, 0.0f, 1.0f, 0.0f), MakeFrame(0.875f, 10.0f, 0.5f, 10.0f), MakeFrame(1.0f, 0.0f, 0.0f, 0.0f)));
	_scalarTracksLooping.push_back(true);




	_shader = new Shader("Shaders/track.vert", "Shaders/track.frag");

	std::vector<glm::vec3> coordinateLinesPos;

	//座標軸
	for (uint32_t i = 0; i < 10; i++) {
		float yPos = (i * 2.0f) + ((float)i * 0.2) + 0.1f;
		float height = 1.8f;

		float left = 1.0f;
		float right = 14.0f;

		//縦軸
		coordinateLinesPos.push_back(glm::vec3(left, yPos, 0));
		coordinateLinesPos.push_back(glm::vec3(left, yPos + height, 0));
		//横軸
		coordinateLinesPos.push_back(glm::vec3(left, yPos, 0));
		coordinateLinesPos.push_back(glm::vec3(right, yPos, 0));
	}
	_coordinateAxis->Set(coordinateLinesPos);

	//グラフ
	for (uint32_t i = 0; i < _scalarTracks.size(); i++) {
		float yPos = ((9 - i) * 2.0f) + ((9 - i) * 0.2f) + 0.1f;
		float height = 1.8f;

		float left = 1.0f;
		float right = 14.0f;
		float xRange = (right - left) / 150.0f;

		for (uint32_t j = 0; j < 149; j++) {
			float thisOrdinalNum = j;
			float nextOrdinalNum = j + 1;
			
			float thisX = left + thisOrdinalNum * xRange;
			float nextX = left + nextOrdinalNum * xRange;

			float thisY = _scalarTracks[i].GetPos(thisOrdinalNum, _scalarTracksLooping[i]);

		}
	}

}

