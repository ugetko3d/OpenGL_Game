#pragma once

class Texture
{
public:
	GLuint ID;

	Texture(const GLchar* path);
	GLvoid bindTexture();
};

