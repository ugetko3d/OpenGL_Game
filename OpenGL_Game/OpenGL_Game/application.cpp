#include <glew.h>
#include <glfw3.h>

#include <iostream>

#include "maths.h"
#include "shader.h"
#include "camera.h"

// Function prototypes
GLvoid framebuffer_size_callback(GLFWwindow* window, GLint width, GLint height);
GLvoid mouse_callback(GLFWwindow* window, GLdouble xpos, GLdouble ypos);
GLvoid scroll_callback(GLFWwindow* window, GLdouble xoffset, GLdouble yoffset);
GLvoid processInput(GLFWwindow *window);

// Window settings
const GLuint WINDOW_WIDTH = 1200;
const GLuint WINDOW_HEIGHT = 600;

// Vertex attributes
const GLuint POSITION = 0;
const GLuint TEXTURE = 1;
const GLuint NORMAL = 2;

// Camera
Camera camera(vec3(0.0f, 0.0f, 5.0f));
GLfloat lastX = WINDOW_WIDTH / 2.0f;
GLfloat lastY = WINDOW_HEIGHT / 2.0f;
GLboolean firstMouse = true;

// Timing
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;

// Object data
const GLfloat cubeVertices[] = {
	// POSITION COORD    // TEXTURE COORD    // NORMAL VECTOR

	-0.5f, -0.5f, +0.5f,	+0.0f, +0.0f,	+0.0f, +0.0f, +1.0f, //FRONT
	+0.5f, -0.5f, +0.5f,	+0.0f, +1.0f,	+0.0f, +0.0f, +1.0f,
	+0.5f, +0.5f, +0.5f,	+1.0f, +1.0f,	+0.0f, +0.0f, +1.0f,
	-0.5f, +0.5f, +0.5f,	+1.0f, +0.0f,	+0.0f, +0.0f, +1.0f,

	-0.5f, -0.5f, +0.5f,	+0.0f, +0.0f,	-1.0f, +0.0f, +0.0f, // LEFT
	-0.5f, +0.5f, +0.5f,	+0.0f, +1.0f,	-1.0f, +0.0f, +0.0f,
	-0.5f, +0.5f, -0.5f,	+1.0f, +1.0f,	-1.0f, +0.0f, +0.0f,
	-0.5f, -0.5f, -0.5f,	+1.0f, +0.0f,	-1.0f, +0.0f, +0.0f,

	-0.5f, -0.5f, -0.5f,	+0.0f, +0.0f,	+0.0f, +0.0f, -1.0f, // BACK
	+0.5f, -0.5f, -0.5f,	+0.0f, +1.0f,	+0.0f, +0.0f, -1.0f,
	+0.5f, +0.5f, -0.5f,	+1.0f, +1.0f,	+0.0f, +0.0f, -1.0f,
	-0.5f, +0.5f, -0.5f,	+1.0f, +0.0f,	+0.0f, +0.0f, -1.0f,

	+0.5f, -0.5f, -0.5f,	+0.0f, +0.0f,	+1.0f, +0.0f, +0.0f, // RIGHT
	+0.5f, +0.5f, -0.5f,	+0.0f, +1.0f,	+1.0f, +0.0f, +0.0f,
	+0.5f, +0.5f, +0.5f,	+1.0f, +1.0f,	+1.0f, +0.0f, +0.0f,
	+0.5f, -0.5f, +0.5f,	+1.0f, +0.0f,	+1.0f, +0.0f, +0.0f,

	-0.5f, +0.5f, +0.5f,	+0.0f, +0.0f,	+0.0f, +1.0f, +0.0f, // TOP
	-0.5f, +0.5f, -0.5f,	+0.0f, +1.0f,	+0.0f, +1.0f, +0.0f,
	+0.5f, +0.5f, -0.5f,	+1.0f, +1.0f,	+0.0f, +1.0f, +0.0f,
	+0.5f, +0.5f, +0.5f,	+1.0f, +0.0f,	+0.0f, +1.0f, +0.0f,

	-0.5f, -0.5f, +0.5f,	+0.0f, +0.0f,	+0.0f, -1.0f, +0.0f, // BOTTOM
	-0.5f, -0.5f, -0.5f,	+0.0f, +1.0f,	+0.0f, -1.0f, +0.0f,
	+0.5f, -0.5f, -0.5f,	+1.0f, +1.0f,	+0.0f, -1.0f, +0.0f,
	+0.5f, -0.5f, +0.5f,	+1.0f, +0.0f,	+0.0f, -1.0f, +0.0f
};

const GLuint cubeIndices[] = {
	0, 1, 2, // FRONT
	0, 3, 2,

	4, 5, 6, // LEFT
	4, 7, 6,

	8, 9, 10, // BACK
	8, 11, 10,

	12, 13, 14, // RIGHT
	12, 15, 14,

	16, 17, 18, // TOP
	16, 19, 18,

	20, 21, 22, // BOTTOM
	20, 23, 22
};

int main()
{
	GLFWwindow* window;

	// Initialize GLFW
	if (!glfwInit())
	{
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	// Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL Flying Game", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// Tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = true;

	// Initialize GLEW
	GLuint glewStatus = glewInit();

	if (glewStatus != GLEW_OK)
	{
		// Problem: glewInit failed, something is seriously wrong
		std::cout << "Error: " << glewGetErrorString(glewStatus) << std::endl;
		return -1;
	}

	// Set global OpenGL state
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	// Printing out useful information to the console
	std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
	std::cout << "Graphics card: " << glGetString(GL_VENDOR)<< " " << glGetString(GL_RENDERER) << std::endl;

	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

	glVertexAttribPointer(POSITION, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(POSITION);

	glVertexAttribPointer(TEXTURE, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(TEXTURE);

	glVertexAttribPointer(NORMAL, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(NORMAL);

	mat4 model = mat4::makeTranslate(vec3(2.0f, 0.0f, -2.0f)) * mat4::makeRotate(38.0f, vec3(5.0f, 10.0f, 5.0f)) * mat4::makeScale(vec3(5.0f, 5.0f, 5.0f));
	mat4 view;
	mat4 projection;

	// Setting up shaders
	Shader objectShader;
	objectShader.init("vertex.shader", "fragment.shader");

	// The model matrix is static, so we pass the model matrix to the shader only once
	objectShader.use();
	objectShader.setMat4("model", model);
	objectShader.setMat4("projection", projection);

	// Setting up textures
	glActiveTexture(GL_TEXTURE0);
	
	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		// Per-frame time logic
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Process player input
		processInput(window);

		// Render here
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Calculate the view matrix
		view = camera.GetViewMatrix();
		projection = mat4::makePerspective(camera.fov, (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);
		
		// The view matrix and projection matrix are changing dynamically, so we pass these matrices to the shader every frame
		objectShader.setMat4("view", view);
		objectShader.setMat4("projection", projection);

		// Draw cube
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	// De-allocate memory on program exit
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}

// ---------------------------------------------------------------------------------------------------------
// PLAYER INPUT
// ---------------------------------------------------------------------------------------------------------
GLvoid processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

// GLFW: whenever the window size changed (by OS or user resize), this callback function executes
GLvoid framebuffer_size_callback(GLFWwindow* window, GLint width, GLint height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


// GLFW: whenever the mouse moves, this callback is called
GLvoid mouse_callback(GLFWwindow* window, GLdouble xpos, GLdouble ypos)
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

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// GLFW: whenever the mouse scroll wheel scrolls, this callback is called
GLvoid scroll_callback(GLFWwindow* window, GLdouble xoffset, GLdouble yoffset)
{
	camera.setFOV(yoffset);
}