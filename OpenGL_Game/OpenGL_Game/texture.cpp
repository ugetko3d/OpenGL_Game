
#include "texture.h"

Texture::Texture()
{

}

Texture::Texture(const std::string& path)
{
	loadTexture(path);
}

void Texture::loadTexture(const std::string& path) 
{
	// Bind texture
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	// Set texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load texture data to buffer
	m_texBuffer = stbi_load(path.c_str(), &m_width, &m_height, &m_channels, 4);

	if (m_texBuffer) {
		// Send texture data to GPU
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_texBuffer);
		// Generate mipmap
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Error: Texture failed to load at path: " << path << std::endl;
	}
	
	// Free data
	stbi_image_free(m_texBuffer);

	// Unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	glDeleteTextures(1, &id);
}

void Texture::bind(unsigned int slot)
{
	glActiveTexture(slot);
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
