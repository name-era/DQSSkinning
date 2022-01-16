#include "attribute.h"


Attribute::Attribute() {
	glGenBuffers(1, &_handle);
	_count = 0;
}

Attribute::~Attribute() {
	glDeleteBuffers(1, &_handle);
}

uint32_t Attribute::GetCount() {
	return _count;
}

uint32_t Attribute::GetHandle() {
	return _handle;
}

uint32_t Attribute::Set(const void* data, uint32_t arrayLength) {
	_count = arrayLength;
	uint32_t size = sizeof(data);

	glBindBuffer(GL_ARRAY_BUFFER, _handle);
	glBufferData(GL_ARRAY_BUFFER, size * _count, data, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Attribute::BindAttribute(uint32_t slot, GLint size) {
	glBindBuffer(GL_ARRAY_BUFFER, _handle);
	glEnableVertexAttribArray(slot);
	glVertexAttribPointer(slot, size, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Attribute::UnBindAttribute(uint32_t slot) {
	glBindBuffer(GL_ARRAY_BUFFER, _handle);
	glDisableVertexAttribArray(slot);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}