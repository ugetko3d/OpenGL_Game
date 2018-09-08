#pragma once

class Window
{
public:
	GLFWwindow* frame;
	const GLchar* TITLE = "OpenGL Game";
	const GLuint WIDTH = 1280;
	const GLuint HEIGHT = 720;

	Window();
	GLvoid prepare();
	GLvoid update();
	GLboolean isClosed();

private:
	GLvoid createDisplay();
	GLvoid startOpenGL();
};




