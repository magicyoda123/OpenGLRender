#pragma once

#include "VertexBuffer.h"

class VertexBufferLayout;

class VertexArray
{
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();

	void AddBufffer(VertexBuffer& vb, VertexBufferLayout& layout);
	void Bind();
	void Unbind();
};