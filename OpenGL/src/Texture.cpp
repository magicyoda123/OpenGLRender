#include "Texture.h"

#include "vendor\stb_image\stb_image.h"

Texture::Texture(const std::string& path)
	:m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr),
	m_Width(0), m_Height(0), m_BPP(0)
{

	stbi_set_flip_vertically_on_load(1);// разные системы координат, в opengl 0,0 bot left ; картинка 0,0 top left
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);// 4 - RGBA 4 канала для текстуры

	GLCall(glGenTextures(1,&m_RendererID)); // генерируем новый айди для текстуры
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)); // устанавливаем параметры  уменьшения текстуры
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)); // MAG - для увеличения текстуры 
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)); // wrap for x
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)); // wrap for y

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height,0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer)); // 8 бит на канал
	GLCall(glBindTexture(GL_TEXTURE_2D,0)); // unbind this texture 

	if (m_LocalBuffer)
		stbi_image_free(m_LocalBuffer); // удаляем текстуру из оперативной памяти. в памяти видеокарты, она остается


}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1,&m_RendererID)); // удаляем текстуру из памяти видеокарты.
}

void Texture::Bind(unsigned int slot)
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot)); // активация текстуры, если несколько текстур.
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Unbind()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0)); // unbind this texture 
}