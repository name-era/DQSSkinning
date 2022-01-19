#include "texture.h"
#include "stb/stb_image.h"
#include "glad/glad.h"

Texture::Texture() {
	_width = 0;
	_height = 0;
	_channels = 0;
	glGenTextures(1, &_handle);
}

Texture::~Texture() {
	glDeleteTextures(1, &_handle);
}

void Texture::Load(const char* path) {
	glBindTexture(GL_TEXTURE_2D, _handle);

	int width, height, channels;
	unsigned char* data = stbi_load(path, &width, &height, &channels, 4);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);

	_width = width;
	_height = height;
	_channels = channels;
}

Texture::Texture(const char* path) {
	glGenTextures(1, &_handle);
	Load(path);
}

void Texture::Set(uint32_t uniformIndex, uint32_t textureIndex) {
	glActiveTexture(GL_TEXTURE0 + textureIndex);
	glBindTexture(GL_TEXTURE_2D, _handle);
	glUniform1i(uniformIndex, textureIndex);
}

void Texture::UnSet(uint32_t textureIndex) {
	glActiveTexture(GL_TEXTURE0 + textureIndex);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);
}

uint32_t Texture::GetHandle() {
	return _handle;
}