#include <glew.h>
#include <glfw3.h>

#include <iostream>

const GLuint POSITION = 0;
const GLuint TEXTURE_COORD = 1;
const GLuint NORMAL = 2;

int main()
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "OpenGL Flying Game", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	GLuint glewStatus = glewInit();

	if (glewStatus != GLEW_OK)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		std::cout << "Error: " << glewGetErrorString(glewStatus) << std::endl;
		return -1;
	}

	std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
	std::cout << glGetString(GL_VENDOR) << " and " << glGetString(GL_RENDERER) << std::endl;

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

	glVertexAttribPointer(TEXTURE_COORD, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(TEXTURE_COORD);

	glVertexAttribPointer(NORMAL, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(NORMAL);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}