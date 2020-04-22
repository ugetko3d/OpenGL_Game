#pragma once

class Window
{
public:
	GLFWwindow* frame;
	const char* TITLE = "OpenGL Game";
	const unsigned int WIDTH = 1280;
	const unsigned int HEIGHT = 720;

	Window();
	float prepareFrame();
	void finishFrame();
	bool isClosed();

private:
	void createDisplay();
	void startOpenGL();
};




