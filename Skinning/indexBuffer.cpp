#include "indexBuffer.h"

IndexBuffer::IndexBuffer() {
	glGenBuffers(1, &_handle);
	_count = 0;
}

IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &_handle);
}

uint32_t IndexBuffer::GetCount() {
	return _count;
}

uint32_t IndexBuffer::GetHandle() {
	return _handle;
}

void IndexBuffer::SetIndex(const void* data, uint32_t arrayLength) {
	_count = arrayLength;
	uint32_t size = sizeof(uint32_t);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _handle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * _count, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}