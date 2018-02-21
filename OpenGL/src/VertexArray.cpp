#include "VertexArray.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBufffer(VertexBuffer& vb, VertexBufferLayout& layout)
{
	Bind();//бинд vetrex array
	vb.Bind();	// бинд буфера
	const auto& elements = layout.GetElements(); // слово auto автоматически определяет тип переменной. получаем элементы vao
	unsigned int offset = 0;
	// установка layout'а 
	for (unsigned int i = 0; i < elements.size(); i++) // для каждого элемента( конкретного vao, их много)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));// линкует в vao данные из buffer
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}
void VertexArray::Bind()
{
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind()
{
	GLCall(glBindVertexArray(0));
}