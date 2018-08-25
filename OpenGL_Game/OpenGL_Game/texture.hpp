#pragma once

class Texture
{
public:
	GLuint ID;

	Texture();
	Texture(const GLchar* path);
	GLvoid bindTexture();
};

