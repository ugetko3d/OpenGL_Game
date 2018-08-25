#pragma once

class Window
{
public:
	GLFWwindow* window;
	const GLchar* TITLE = "OpenGL Game";
	const GLuint WIDTH = 1200;
	const GLuint HEIGHT = 600;

	GLvoid initGLFW();
	GLvoid initGLEW();
	GLvoid finishFrame();
};




