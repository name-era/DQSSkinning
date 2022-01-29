#pragma once
#include "indexBuffer.h"

enum class DrawMode {
	Points,
	LineStrip,
	LineLoop,
	Lines,
	Triangles,
	TriangleStrip,
	TriangleFan
};

/**
* ���_��`�悷��
*/
void ExecuteDraw(uint32_t vertexCount, DrawMode mode);

/**
* �C���f�b�N�X���w�肷�钸�_��`�悷��
*/
void Draw(IndexBuffer& inIndexBuffer, DrawMode mode);

/**
* ���_���C���X�^���X�`�悷��
*/
void DrawInstanced(uint32_t vertexCount, DrawMode mode, uint32_t instanceCount);

/**
* �C���f�b�N�X���w�肷�钸�_���C���X�^���X�`�悷��
*/
void DrawInstanced(IndexBuffer& inIndexBuffer, DrawMode mode, uint32_t instanceCount);
