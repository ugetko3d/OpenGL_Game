#pragma once

#include "glew.h"

class texture
{
public:
	GLuint ID, index;

	texture();
	texture(const GLchar* path);
	GLvoid activateTexture();
	GLvoid bindTexture();
};

