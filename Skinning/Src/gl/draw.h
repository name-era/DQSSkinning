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
* 頂点を描画する
*/
void Draw(uint32_t vertexCount, DrawMode mode);

/**
* インデックスが指定する頂点を描画する
*/
void Draw(IndexBuffer& inIndexBuffer, DrawMode mode);

/**
* 頂点をインスタンス描画する
*/
void DrawInstanced(uint32_t vertexCount, DrawMode mode, uint32_t instanceCount);

/**
* インデックスが指定する頂点をインスタンス描画する
*/
void DrawInstanced(IndexBuffer& inIndexBuffer, DrawMode mode, uint32_t instanceCount);
