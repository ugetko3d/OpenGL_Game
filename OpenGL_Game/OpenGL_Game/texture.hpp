#pragma once

#include "glew.h"

class Texture
{
public:
	GLuint ID, index;

	Texture();
	Texture(const GLchar* path);
	GLvoid bindTexture();
};

