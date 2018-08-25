#include <glew.h>
#include <glfw3.h>

#include <iostream>

#include "window.hpp"

GLvoid Window::initGLFW()
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
	window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	// Make the window's context current
	glfwMakeContextCurrent(window);

	// Tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

GLvoid Window::initGLEW()
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

GLvoid Window::finishFrame()
{
	// Swap front and back buffers
	glfwSwapBuffers(window);

	// Poll for and process events
	glfwPollEvents();
}