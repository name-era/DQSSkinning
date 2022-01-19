#include "attribute.h"
#include "glad/glad.h"

template Attribute<glm::vec2>;
template Attribute<glm::vec3>;
template Attribute<glm::vec4>;
template Attribute<uint32_t>;
template Attribute<float>;

template<typename T>
Attribute<T>::Attribute() {
	glGenBuffers(1, &_handle);
	_count = 0;
}

template<typename T>
Attribute<T>::~Attribute() {
	glDeleteBuffers(1, &_handle);
}

template<typename T>
uint32_t Attribute<T>::GetCount() {
	return _count;
}

template<typename T>
uint32_t Attribute<T>::GetHandle() {
	return _handle;
}

template<typename T>
void Attribute<T>::Set(T* inputArray, uint32_t arrayLength) {
	_count = arrayLength;
	uint64_t size = sizeof(T);

	glBindBuffer(GL_ARRAY_BUFFER, _handle);
	glBufferData(GL_ARRAY_BUFFER, size * _count, inputArray, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

template<typename T>
void Attribute<T>::Set(std::vector<T>& input) {
	Set(&input[0], (uint32_t)input.size());
}

template<>
void Attribute<uint32_t>::SetAttributePointer(uint32_t slot) {
	glVertexAttribPointer(slot, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

template<>
void Attribute<float>::SetAttributePointer(uint32_t slot) {
	glVertexAttribPointer(slot, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

template<>
void Attribute<glm::vec2>::SetAttributePointer(uint32_t slot) {
	glVertexAttribPointer(slot, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

template<>
void Attribute<glm::vec3>::SetAttributePointer(uint32_t slot) {
	glVertexAttribPointer(slot, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

template<>
void Attribute<glm::vec4>::SetAttributePointer(uint32_t slot) {
	glVertexAttribPointer(slot, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

template<>
void Attribute<glm::quat>::SetAttributePointer(uint32_t slot) {
	glVertexAttribPointer(slot, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

template<typename T>
void Attribute<T>::BindTo(uint32_t slot) {
	glBindBuffer(GL_ARRAY_BUFFER, _handle);
	glEnableVertexAttribArray(slot);
	SetAttributePointer(slot);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

template<typename T>
void Attribute<T>::UnBind(uint32_t slot) {
	glBindBuffer(GL_ARRAY_BUFFER, _handle);
	glDisableVertexAttribArray(slot);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}