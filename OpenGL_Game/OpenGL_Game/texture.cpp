#include <glew.h>

#include <iostream>
#include <string>
#include "stb_image.h"

#include "texture.h"

Texture::Texture(const std::string& path)
{
	int nrChannels, width, height;
	unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	if (!data) {
		std::cout << "Error: Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	m_width = width;
	m_height = height;

	glGenTextures(1, &m_texID);
	glBindTexture(GL_TEXTURE_2D, m_texID);

	// Bind texture and generate mipmap
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Set texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Free data and unbind texture
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_texID);
}

void Texture::Activate(unsigned int textureUnit)
{
	glActiveTexture(textureUnit);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_texID);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
