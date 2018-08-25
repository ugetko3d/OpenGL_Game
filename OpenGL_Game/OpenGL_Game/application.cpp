#include <glew.h>
#include <glfw3.h>
#include "window.hpp"

#include <iostream>

#include "maths.hpp"
#include "shader.hpp"
#include "camera.hpp"
#include "texture.hpp"

Window screen;

// Vertex attributes
const GLuint POSITION = 0;
const GLuint TEXTURE = 1;
const GLuint NORMAL = 2;

// Camera
Camera camera(vec3(0.0f, 0.0f, 5.0f));
GLfloat lastX = screen.WIDTH / 2.0f;
GLfloat lastY = screen.HEIGHT / 2.0f;
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

GLvoid framebuffer_size_callback(GLFWwindow* window, GLint width, GLint height);
GLvoid mouse_callback(GLFWwindow* window, GLdouble xpos, GLdouble ypos);
GLvoid scroll_callback(GLFWwindow* window, GLdouble xoffset, GLdouble yoffset);
GLvoid processInput(GLFWwindow* window);

int main()
{
	screen.initGLFW();

	glfwSetFramebufferSizeCallback(screen.window, framebuffer_size_callback);
	glfwSetCursorPosCallback(screen.window, mouse_callback);
	glfwSetScrollCallback(screen.window, scroll_callback);

	screen.initGLEW();

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
	Shader objectShader("vertex.shader", "fragment.shader");

	// The model matrix is static, so we pass the model matrix to the shader only once
	objectShader.use();
	objectShader.setMat4("model", model);
	objectShader.setMat4("projection", projection);
	objectShader.setInt("tex", 0);

	// Setting up textures
	Texture tex("stones.jpg");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex.ID);
	
	// Loop until the user closes the window
	while (!glfwWindowShouldClose(screen.window))
	{
		// Per-frame time logic
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Process player input
		processInput(screen.window);

		// Render here
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Calculate the view and projection matrix
		view = camera.getViewMatrix();
		projection = mat4::makePerspective(camera.fov, (GLfloat)screen.WIDTH / (GLfloat)screen.HEIGHT, 0.1f, 100.0f);
		
		// The view matrix and projection matrix are changing dynamically, so we pass these matrices to the shader every frame
		objectShader.setMat4("view", view);
		objectShader.setMat4("projection", projection);

		// Draw cube
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		screen.finishFrame();
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
GLvoid processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.processKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.processKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.processKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.processKeyboard(RIGHT, deltaTime);
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

	camera.processMouseMovement(xoffset, yoffset);
}

// GLFW: whenever the mouse scroll wheel scrolls, this callback is called
GLvoid scroll_callback(GLFWwindow* window, GLdouble xoffset, GLdouble yoffset)
{
	camera.setFOV(yoffset);
}