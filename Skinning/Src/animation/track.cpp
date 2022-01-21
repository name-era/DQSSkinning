#include "track.h"

template Track<float, 1>;
template Track<glm::vec3, 3>;
template Track<glm::quat, 4>;

template<typename T, uint32_t N>
void Track<T, N>::SetInterpolation(Interpolation interpolation) {
	_interpolation = interpolation;
}

template<typename T, uint32_t N>
void Track<T, N>::Resize(uint32_t size) {
	_frames.resize(size);
}

template<typename T, uint32_t N>
Frame<N>& Track<T, N>::operator[](uint32_t index) {
	_frames[index];
}