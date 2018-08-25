#include <glew.h>

#include <iostream>
#include "stb_image.h"

#include "texture.hpp"

Texture::Texture(const GLchar* path)
{
	GLint width, height, nrChannels;
	unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (!data) {
		std::cout << "Error: Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	glGenTextures(1, &this->ID);
	glBindTexture(GL_TEXTURE_2D, this->ID);

	// Bind texture and generate mipmap
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
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

GLvoid Texture::bindTexture()
{
	glBindTexture(GL_TEXTURE_2D, this->ID);
}
