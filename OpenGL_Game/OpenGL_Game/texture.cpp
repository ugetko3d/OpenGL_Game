#include <iostream>

#include "stb_image.h"

#include "texture.hpp"

texture::texture()
{

}

texture::texture(const GLchar* path)
{
	glGenTextures(1, &ID);

	GLint nrChannels, width, height;
	unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (!data) {
		printf("Error: Texture failed to load at path: %s", path);
		stbi_image_free(data);
	}

	GLenum format;
	if (nrChannels == 1)
		format = GL_RED;
	else if (nrChannels == 3)
		format = GL_RGB;
	else if (nrChannels == 4)
		format = GL_RGBA;

	// Bind texture and generate mipmap
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Free data and unbind texture
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLvoid texture::bindTexture()
{
	glBindTexture(GL_TEXTURE_2D, this->ID);
}
