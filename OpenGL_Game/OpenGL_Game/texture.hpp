#pragma once

#include "glew.h"

class Texture
{
public:
	GLuint ID;

	Texture();
	Texture(const GLchar* path);
	GLvoid bindTexture();
};

