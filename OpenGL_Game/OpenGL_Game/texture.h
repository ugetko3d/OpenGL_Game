#pragma once

#include <glew.h>
#include "stb_image.h"
#include <iostream>

class Texture
{
private:
	int m_width, m_height, m_channels;
	std::string m_filePath;
	unsigned char* m_texBuffer;
public:
	unsigned int id;

	Texture();
	Texture(const std::string& path);
	~Texture();

	void loadTexture(const std::string& path);
	void bind(unsigned int slot);
	void unbind();
};

