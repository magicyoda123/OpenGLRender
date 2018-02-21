#define _CRT_SECURE_NO_WARNINGS
#include "Shader.h"
#include "mylib.h"
#include <iostream>
#include <stdio.h>
#include "Renderer.h"


Shader::Shader(const std::string& filepath)
	:m_FilePath(filepath), m_RendererID(0)
{
	
	shadersource test = ParseShader(filepath);
	m_RendererID = CreateShader(test.VetexSource, test.FragmentSource);


}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererID));
}

shadersource Shader::ParseShader(const std::string& filepath)
{
	FILE *shaderFile = fopen(filepath.c_str(), "r"); // открыть файл для чтения
	int cur;
	int count = 0;
	char *fileText = NULL;
	char vertexShader[1000];
	char fragmentShader[1000];

	do
	{
		cur = getc(shaderFile);
		if (cur != NULL)
		{
			count++;
			fileText = (char *)realloc(fileText, sizeof(char)*count); // динамически выделить память для нового символа
			fileText[count - 1] = cur; // записываем в массив весь текст из файла.
		}
	} while (cur != EOF);


	int shaderVertexBegin = searchText(fileText, "#shader vertex") + strlen("#shader vertex"); // номер с которого начинается вершинный шейдер
	int shaderVertexEnd = searchText(fileText, "#shader fragment") - 1;
	int shaderFragmentBegin = shaderVertexEnd + strlen("#shader fragment") + 1; // номер с которого начинается фргментный шейдер
	int shaderFragmentEnd = count;
	memcpy(vertexShader, fileText + shaderVertexBegin *sizeof(char), shaderVertexEnd - shaderVertexBegin + 1); // записать в мссив vertexShader текст с шейдером
	memcpy(fragmentShader, fileText + shaderFragmentBegin * sizeof(char), shaderFragmentEnd - shaderFragmentBegin); // зписать в массив fragmentShader текст с шейдером


	int lShaderVertex = shaderVertexEnd - shaderVertexBegin + 1;
	int lShaderFragment = shaderFragmentEnd - shaderFragmentBegin;
	char *a;
	a = (char*)malloc((lShaderVertex + 1)*sizeof(char));
	for (int i = 0; i < lShaderVertex; i++)
	{
		a[i] = vertexShader[i];

	}
	a[lShaderVertex] = '\0';
	char *b;
	b = (char*)malloc((lShaderFragment + 1)*sizeof(char));
	for (int i = 0; i < lShaderFragment; i++)
	{
		b[i] = fragmentShader[i];
	}
	b[lShaderFragment] = '\0';
	return{ a, b };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);// задаем уникальный номер нашему будущему шейдеру
	const char* src = source.c_str();// указатель на начало строки с шейдером
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	// TODO: ERROR HANDLING

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char *message = (char *)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " <<
			(type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}
	return id;
}
unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();// задаем уникальный номер программе
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	glAttachShader(program, vs);// связываем много шейдеров в одну программу
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);


	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void Shader::Bind()
{
	GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind()
{
	GLCall(glUseProgram(0));
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) // если в таблице у нас уже есть такая запись
		return m_UniformLocationCache[name];
	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str())); // узнаем адрес переменной в которую будем передавать uniforms значения

	if (location == -1)
	std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
	m_UniformLocationCache[name] = location;
	return location;
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));

}

void Shader::SetUniform1i(const std::string& name, int value)
{
	
	GLCall(glUniform1i(GetUniformLocation(name), value));
}