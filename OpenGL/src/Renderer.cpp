#include "Renderer.h"
#include <iostream>
#include <stdio.h>

void  GLClearError() // ������� ������� �� ���������� ������ � openGL
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) // ������� ������ ���� ������ � openGL
{
	while (GLenum error = glGetError())
	{
		printf("[OpenGL error] 0x%04x ", error); // ����� � 16 ������ ������� ��������� ������
		std::cout << function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}

void Renderer::Clear()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(VertexArray& va,  IndexBuffer& ib, Shader& shader)
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));// ��������� ��������� ������ �������
}