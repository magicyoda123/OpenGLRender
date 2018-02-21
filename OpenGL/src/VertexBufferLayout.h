#pragma once

#include "GL\glew.h"
#include "Renderer.h"
#include <vector>

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count; 
	unsigned char normalized;// нормализация, для упрощения работы клиппера в координаты [-1;1]
	
	static unsigned int GetSizeOfType( unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT :			return 4;
		case GL_UNSIGNED_INT:	return 4;
		case  GL_UNSIGNED_BYTE: return 1;
		}
		ASSERT(false);
		return 0;
	}

};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
public:
	VertexBufferLayout()
		: m_Stride(0){}

	template<typename T>
	void Push(int count)
	{
		static_assert(false); // прекращение работы, если переданы данные не типа float
	}

	template<>
	void Push<float>(int count)
	{
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });// добавление нового элемента в конец вектора(шаблон класса представляет из себя динамический массив)
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>( int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });// добавление нового элемента в конец вектора(шаблон класса представляет из себя динамический массив)
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<unsigned char>(int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });// добавление нового элемента в конец вектора(шаблон класса представляет из себя динамический массив)
		m_Stride += count *VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; } // stride - шагать, шаг

};