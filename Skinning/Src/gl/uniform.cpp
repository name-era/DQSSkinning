#include "uniform.h"
#include "glad/glad.h"

template Uniform<int>;
template Uniform<float>;
template Uniform<glm::vec2>;
template Uniform<glm::vec3>;
template Uniform<glm::vec4>;
template Uniform<glm::quat>;
template Uniform<glm::mat4>;


#define UNIFORM_IMPL(gl_func, tType, dType) \
template<> \
void Uniform<tType>::Set(uint32_t slot, tType* data, uint32_t length) { \
    gl_func(slot, (GLsizei)length, (dType*)&data[0]); \
}

UNIFORM_IMPL(glUniform1iv, int, int)
UNIFORM_IMPL(glUniform1fv, float, float)
UNIFORM_IMPL(glUniform2fv, glm::vec2, float)
UNIFORM_IMPL(glUniform3fv, glm::vec3, float)
UNIFORM_IMPL(glUniform4fv, glm::vec4, float)
UNIFORM_IMPL(glUniform4fv, glm::quat, float)

template<>
void Uniform<glm::mat4>::Set(uint32_t slot, glm::mat4* inputArray, uint32_t arrayLength) {
	glUniformMatrix4fv(slot, arrayLength, false, (float*)&inputArray[0]);
}

template <typename T>
void Uniform<T>::Set(uint32_t slot, const T& value) {
	Set(slot, (T*)&value, 1);
}

template <typename T>
void Uniform<T>::Set(uint32_t slot, std::vector<T>& value) {
	Set(slot, &value[0], (uint32_t)value.size());
}