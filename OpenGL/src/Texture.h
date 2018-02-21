#pragma once

#include "Renderer.h"

class Texture
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer; // массив, где хранится текстура
	int m_Width, m_Height, m_BPP;// BPP - Bits per pixel битов на пиксель в нашем файле.

public:
	Texture(const std::string& path);
	~Texture();
	void Bind(unsigned int slot = 0);
	void Unbind();

	inline int GetWidth() { return m_Width; }
	inline int GetHeight() { return m_Height; }
};