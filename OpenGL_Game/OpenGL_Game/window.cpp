#include <glew.h>
#include <glfw3.h>

#include <iostream>

#include "window.hpp"

GLboolean firstMouse = true;
GLfloat lastX;
GLfloat lastY;

void resizeWindow(GLFWwindow* frame, int width, int height);
GLvoid mouseMoved(GLFWwindow* frame, GLdouble xpos, GLdouble ypos);
GLvoid mouseScrolled(GLFWwindow* frame, GLdouble xoffset, GLdouble yoffset);

Window::Window()
{
	initGLFW();
	initGLEW();
}

Window::~Window()
{
	glfwTerminate();
}

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
	frame = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
	if (!frame)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	// Make the window's context current
	glfwMakeContextCurrent(frame);

	glfwSetFramebufferSizeCallback(frame, resizeWindow);
	glfwSetCursorPosCallback(frame, mouseMoved);
	glfwSetScrollCallback(frame, mouseScrolled);

	// Tell GLFW to capture our mouse
	glfwSetInputMode(frame, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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

GLboolean Window::closed()
{
	return glfwWindowShouldClose(frame);
}

// ---------------------------------------------------------------------------------------------------------
// PLAYER INPUT
// ---------------------------------------------------------------------------------------------------------
GLvoid Window::processInput(GLfloat deltaTime)
{
	if (glfwGetKey(frame, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(frame, true);
	}
	if (glfwGetKey(frame, GLFW_KEY_W) == GLFW_PRESS)
	{
		Camera::processKeyboard(FORWARD, deltaTime);
	}
	if (glfwGetKey(frame, GLFW_KEY_S) == GLFW_PRESS)
	{
		Camera::processKeyboard(BACKWARD, deltaTime);
	}
	if (glfwGetKey(frame, GLFW_KEY_A) == GLFW_PRESS)
	{
		Camera::processKeyboard(LEFT, deltaTime);
	}
	if (glfwGetKey(frame, GLFW_KEY_D) == GLFW_PRESS)
	{
		Camera::processKeyboard(RIGHT, deltaTime);
	}
}

// GLFW: whenever the window size changed (by OS or user resize), this callback function executes
void resizeWindow(GLFWwindow* frame, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// GLFW: whenever the mouse moves, this callback is called
GLvoid mouseMoved(GLFWwindow* frame, GLdouble xpos, GLdouble ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	Camera::processMouseMovement(xoffset, yoffset);
}

// GLFW: whenever the mouse scroll wheel scrolls, this callback is called
GLvoid mouseScrolled(GLFWwindow* frame, GLdouble xoffset, GLdouble yoffset)
{
	Camera::setFOV(yoffset);
}
