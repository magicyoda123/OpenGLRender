#pragma once

#include <GL/glew.h>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

#define ASSERT(x) if  (!(x)) __debugbreak();
#ifdef _DEBUG
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
#define	GLCall(x) x
#endif
void  GLClearError(); // функция очистки от предыдущих ошибок в openGL
bool GLLogCall(const char* function, const char* file, int line); // функция вывода кода ошибки в openGL

class Renderer
{
public:
	void Clear();
	void Draw(VertexArray& va, IndexBuffer& ib, Shader& shader);
};