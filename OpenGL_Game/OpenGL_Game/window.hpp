#pragma once

#include "camera.hpp"

class Window
{
public:
	GLFWwindow* frame;
	const GLchar* TITLE = "OpenGL Game";
	const GLuint WIDTH = 1200;
	const GLuint HEIGHT = 600;

	Window();
	~Window();
	GLvoid prepare();
	GLvoid update();
	GLboolean closed();
	GLvoid processInput(GLfloat deltaTime);
private:
	GLvoid initGLFW();
	GLvoid initGLEW();
};




