#pragma once
#include "track.h"
#include "shader.h"
#include "attribute.h"
#include <vector>


class Graph {
protected:
	std::vector<ScalarTrack> _scalarTracks;
	std::vector<bool> _scalarTracksLooping;


	Shader* _shader;
	//ç¿ïWé≤
	Attribute<glm::vec3>* _coordinateAxis;
	//lines
	Attribute<glm::vec3>* _scalarTrackLines;
	//êßå‰ì_
	Attribute<glm::vec3>* _controledPoints;
	//êßå‰ê¸
	Attribute<glm::vec3>* _tangentLines;

private:
	ScalarTrack MakeScalarTrack(Interpolation interp, uint32_t numFrames, ...);

	ScalarFrame MakeFrame(float time, float in, float value, float out);
	ScalarFrame MakeFrame(float time, float value);
	VectorFrame MakeFrame(float time, const glm::vec3& in, const glm::vec3& value, const glm::vec3& out);
	VectorFrame MakeFrame(float time, const glm::vec3& value);
	QuartanionFrame MakeFrame(float time, const glm::quat& in, const glm::quat& out, const glm::quat& value);
	QuartanionFrame MakeFrame(float time, const glm::quat& value);

public:
	void Initialize();
};