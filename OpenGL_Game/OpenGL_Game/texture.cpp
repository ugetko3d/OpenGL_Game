
#include "texture.h"

Texture::Texture()
{

}

Texture::Texture(const std::string& path)
{
	loadTexture(path);
}

Texture::~Texture()
{

}

void Texture::loadTexture(const std::string& path)
{
	// Bind texture
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	// Set texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);

	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load texture data to buffer
	m_texBuffer = stbi_load(path.c_str(), &m_width, &m_height, &m_channels, 0);

	if (m_texBuffer)
	{
		// Send texture data to GPU
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_texBuffer);
		// Generate mipmap
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Error: Texture failed to load at path: " << path << std::endl;
	}

	// Free data
	stbi_image_free(m_texBuffer);

	// Unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
}
