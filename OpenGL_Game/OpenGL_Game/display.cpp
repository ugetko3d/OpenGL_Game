#include <glew.h>
#include <glfw3.h>

#include <iostream>

#include "display.hpp"

Window::Window()
{
	createDisplay();
	startOpenGL();
}

GLvoid Window::createDisplay()
{
	// Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	// Create a windowed mode window and its OpenGL context
	frame = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
	if (!frame)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	// Make the window's context current
	glfwMakeContextCurrent(frame);

	// Tell GLFW to capture our mouse
	glfwSetInputMode(frame, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

GLvoid Window::startOpenGL()
{
	glewExperimental = true;

	// Initialize GLEW
	GLuint glewStatus = glewInit();

	if (glewStatus != GLEW_OK)
	{
		// Problem: glewInit failed, something is seriously wrong
		std::cout << "Error: " << glewGetErrorString(glewStatus) << std::endl;
		exit(EXIT_FAILURE);
	}

	// Set global OpenGL state
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	// Printing out useful information to the console
	std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
	std::cout << "Graphics card: " << glGetString(GL_VENDOR) << " " << glGetString(GL_RENDERER) << std::endl;
}

GLvoid Window::prepare()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

GLvoid Window::update()
{
	// Swap front and back buffers
	glfwSwapBuffers(frame);

	// Poll for and process events
	glfwPollEvents();
}

GLboolean Window::isClosed()
{
	return glfwWindowShouldClose(frame);
}
