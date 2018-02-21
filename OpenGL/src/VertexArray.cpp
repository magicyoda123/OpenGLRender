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
	Bind();//���� vetrex array
	vb.Bind();	// ���� ������
	const auto& elements = layout.GetElements(); // ����� auto ������������� ���������� ��� ����������. �������� �������� vao
	unsigned int offset = 0;
	// ��������� layout'� 
	for (unsigned int i = 0; i < elements.size(); i++) // ��� ������� ��������( ����������� vao, �� �����)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));// ������� � vao ������ �� buffer
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