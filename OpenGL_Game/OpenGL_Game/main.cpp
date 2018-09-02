#include <glew.h>
#include <glfw3.h>
#include "window.hpp"

#include <iostream>

#include "maths.hpp"
#include "shader.hpp"
#include "texture.hpp"

// Window
Window window;

// Vertex attributes
const GLuint POSITION = 0;
const GLuint TEXTURE = 1;
const GLuint NORMAL = 2;

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

	// Camera
	Camera::init();
	
	// Loop until the user closes the window
	while (!window.closed())
	{
		// Per-frame time logic
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		window.prepare();

		// Process player input
		window.processInput(deltaTime);

		// Calculate the view and projection matrix
		view = Camera::getViewMatrix();
		projection = mat4::makePerspective(Camera::fov, (GLfloat)window.WIDTH / (GLfloat)window.HEIGHT, 0.1f, 100.0f);
		
		// The view matrix and projection matrix are changing dynamically, so we pass these matrices to the shader every frame
		objectShader.setMat4("view", view);
		objectShader.setMat4("projection", projection);

		// Draw cube
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		window.update();
	}

	// De-allocate memory on program exit
	glDeleteVertexArrays(1, &VAO);
	glDeleteTextures(1, &tex.ID);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}





