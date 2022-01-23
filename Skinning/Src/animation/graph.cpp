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

	_shader = new Shader("Shaders/track.vert", "Shaders/track.frag");
	_coordinateAxis = new Attribute<glm::vec3>();
	_scalarTrackLines = new Attribute<glm::vec3>();
	_controledPoints = new Attribute<glm::vec3>();
	_tangentLines = new Attribute<glm::vec3>();

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
		float time = i / 10.0f * 0.5f + 0.25f;
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

	std::vector<glm::vec3> coordinateLinesPos;

	//座標軸
	for (uint32_t i = 0; i < 10; i++) {
		float yPos = (i * 2.0f) + (i * 0.2f) + 0.1f;
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
	std::vector<glm::vec3> graphPos;
	//制御点
	std::vector<glm::vec3> controledPos;
	std::vector<glm::vec3> controledLines;

	for (uint32_t i = 0; i < _scalarTracks.size(); i++) {
		float bottom = ((9 - i) * 2.0f) + ((9 - i) * 0.2f) + 0.1f;
		float height = 1.8f;

		float left = 1.0f;
		float right = 14.0f;
		float xRange = right - left;


		for (uint32_t j = 0; j < 149; j++) {
			float thisOrdinalNum = j / 149.0f;
			float nextOrdinalNum = (j + 1) / 149.0f;
			
			float thisX = left + thisOrdinalNum * xRange;
			float nextX = left + nextOrdinalNum * xRange;

			float thisY = _scalarTracks[i].GetValue(thisOrdinalNum, _scalarTracksLooping[i]);
			float nextY = _scalarTracks[i].GetValue(nextOrdinalNum, _scalarTracksLooping[i]);

			thisY = bottom + thisY * height;
			nextY = bottom + nextY * height;

			graphPos.push_back(glm::vec3(thisX, thisY, 0.1f));
			graphPos.push_back(glm::vec3(nextX, nextY, 0.1f));
		}
		
		if (_scalarTracks[i].GetInterpolation() != Interpolation::Constant) {
			for (uint32_t j = 0; j < _scalarTracks[i].GetSize(); j++) {
				//time：0.0〜1.0
				float thisTime = _scalarTracks[i][j].time;
				float thisY = bottom + _scalarTracks[i].GetValue(thisTime, _scalarTracksLooping[i]) * height;
				float thisX = left + thisTime * xRange;
				controledPos.push_back(glm::vec3(thisX, thisY, 0.9f));

				if (j > 0) {
					//微小時間ずらす
					float prevY = bottom + _scalarTracks[i].GetValue(thisTime - 0.0001f, _scalarTracksLooping[i]) * height;
					float prevX = left + (thisTime - 0.0001f) * xRange;

					glm::vec3 thisPos = glm::vec3(thisX, thisY, 0.6f);
					glm::vec3 prevPos = glm::vec3(prevX, prevY, 0.6f);
					glm::vec3 handledPos = thisPos + glm::normalize(prevPos - thisPos);

					controledLines.push_back(thisPos);
					controledLines.push_back(handledPos);
				}

				//線形補間とキュービック補間をするときは次のトラックの制御線も描画する
				if (j < _scalarTracks[i].GetSize() - 1) {
					float nextY = bottom + _scalarTracks[i].GetValue(thisTime + 0.0001f, _scalarTracksLooping[i]) * height;
					float nextX = left + (thisTime + 0.0001f) * xRange;

					glm::vec3 thisPos = glm::vec3(thisX, thisY, 0.6f);
					glm::vec3 nextPos = glm::vec3(nextX, nextY, 0.6f);
					glm::vec3 handledPos = thisPos + glm::normalize(nextPos - thisPos);

					controledLines.push_back(thisPos);
					controledLines.push_back(handledPos);
				}
			}
		}
	}
	_scalarTrackLines->Set(graphPos);
	_controledPoints->Set(controledPos);
	_tangentLines->Set(controledLines);
}

void Graph::DrawGraph(GraphDrawMode mode, const glm::vec3& color, const glm::mat4& mvp, Attribute<glm::vec3>* attribute) {
	_shader->Bind();
	Uniform <glm::mat4>::Set(_shader->GetUniformIndex("mvp"), mvp);
	Uniform<glm::vec3>::Set(_shader->GetUniformIndex("color"), color);
	attribute->BindTo(_shader->GetAttributeIndex("position"));

	if (mode == GraphDrawMode::Lines) {
		Draw(attribute->GetCount(), DrawMode::Lines);
	}
	else if (mode == GraphDrawMode::Loop) {
		Draw(attribute->GetCount(), DrawMode::LineLoop);
	}
	else if (mode == GraphDrawMode::Strip) {
		Draw(attribute->GetCount(), DrawMode::LineStrip);
	}
	else {
		Draw(attribute->GetCount(), DrawMode::Points);
	}

	attribute->UnBind(_shader->GetAttributeIndex("position"));
	_shader->UnBind();
}

void Graph::Render(float aspectRatio) {
	glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 projection = glm::ortho(0.0f, aspectRatio * 25.0f, 0.0f, 25.0f, 0.001f, 10.0f);
	glm::mat4 mvp = projection * view;

	DrawGraph(GraphDrawMode::Lines, glm::vec3(1, 1, 1), mvp, _coordinateAxis);
	DrawGraph(GraphDrawMode::Lines, glm::vec3(0, 1, 0), mvp, _scalarTrackLines);
	DrawGraph(GraphDrawMode::Points, glm::vec3(0, 0, 1), mvp, _controledPoints);
	DrawGraph(GraphDrawMode::Lines, glm::vec3(1, 0, 0), mvp, _tangentLines);
}

void Graph::ShutDown() {
	_scalarTracks.clear();
	_scalarTracksLooping.clear();

	delete _shader;
	delete _coordinateAxis;
	delete _scalarTrackLines;
	delete _controledPoints;
	delete _tangentLines;
}

