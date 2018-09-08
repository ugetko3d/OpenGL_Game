#pragma once

class Window
{
public:
	GLFWwindow* frame;
	const GLchar* TITLE = "OpenGL Game";
	const GLuint WIDTH = 1280;
	const GLuint HEIGHT = 720;

	Window();
	GLfloat prepareFrame();
	GLvoid finishFrame();
	GLboolean isClosed();

private:
	GLvoid createDisplay();
	GLvoid startOpenGL();
};




