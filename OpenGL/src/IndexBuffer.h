#pragma once

class IndexBuffer
{
private:
	unsigned int m_RendererID; //  opengl id
	unsigned int m_Count; //число вершин
public:
	IndexBuffer(const unsigned int*	data, unsigned int count);
	~IndexBuffer();

	void Bind();
	void Unbind();

	unsigned int GetCount();
};