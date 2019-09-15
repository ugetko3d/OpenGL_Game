#include <glew.h>

#include "comm.h"
#include <glfw3.h>
#include "display.h"

#include "maths.h"
#include "shader.h"
#include "texture.h"
#include "camera.h"

#include "vertex_array.h"
#include "vertex_buffer.h"
#include "index_buffer.h"

// Processes input
GLvoid processInput(GLFWwindow* frame, GLfloat deltaTime);
GLvoid resizeWindow(GLFWwindow* frame, GLint width, GLint height);
GLvoid mouseMoved(GLFWwindow* frame, GLdouble xpos, GLdouble ypos);
GLvoid mouseScrolled(GLFWwindow* frame, GLdouble xoffset, GLdouble yoffset);

const enum attrib
{
	POSITION, TEXTURE, NORMAL
};

// Window
Window window;

// Camera
Camera camera;
GLboolean firstMouse = true;
GLfloat lastX = window.WIDTH / 2;
GLfloat lastY = window.HEIGHT / 2;

// Lighting
vec3 lightPos(5.0f, 5.0f, 5.0f);

// Object data
float vertices[] = {
	// POSITION COORD    // TEXTURE COORD    // NORMAL VECTOR

	// Back
	-0.5f, -0.5f, -0.5f,    1.0f, 0.0f,		0.0f, 0.0f, -0.5f,
	+0.5f, -0.5f, -0.5f,    0.0f, 0.0f,		0.0f, 0.0f, -0.5f,
	+0.5f, +0.5f, -0.5f,    0.0f, 1.0f,		0.0f, 0.0f, -0.5f,
	+0.5f, +0.5f, -0.5f,	0.0f, 1.0f,		0.0f, 0.0f, -0.5f,
	-0.5f, +0.5f, -0.5f,	1.0f, 1.0f,		0.0f, 0.0f, -0.5f,
	-0.5f, -0.5f, -0.5f,	1.0f, 0.0f,		0.0f, 0.0f, -0.5f,

	// Front
	-0.5f, -0.5f, +0.5f,	0.0f, 0.0f,		0.0f, 0.0f, +0.5f,
	+0.5f, -0.5f, +0.5f,	1.0f, 0.0f,		0.0f, 0.0f, +0.5f,
	+0.5f, +0.5f, +0.5f,	1.0f, 1.0f,		0.0f, 0.0f, +0.5f,
	+0.5f, +0.5f, +0.5f,	1.0f, 1.0f,		0.0f, 0.0f, +0.5f,
	-0.5f, +0.5f, +0.5f,	0.0f, 1.0f,		0.0f, 0.0f, +0.5f,
	-0.5f, -0.5f, +0.5f,	0.0f, 0.0f,		0.0f, 0.0f, +0.5f,

	// Left
	-0.5f, +0.5f, +0.5f,	1.0f, 1.0f,		-0.5f, 0.0f, 0.0f,
	-0.5f, +0.5f, -0.5f,	0.0f, 1.0f,		-0.5f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,		-0.5f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,		-0.5f, 0.0f, 0.0f,
	-0.5f, -0.5f, +0.5f,	1.0f, 0.0f,		-0.5f, 0.0f, 0.0f,
	-0.5f, +0.5f, +0.5f,	1.0f, 1.0f,		-0.5f, 0.0f, 0.0f,

	// Right
	+0.5f, +0.5f, +0.5f,	0.0f, 1.0f,		+0.5f, 0.0f, 0.0f,
	+0.5f, +0.5f, -0.5f,	1.0f, 1.0f,		+0.5f, 0.0f, 0.0f,
	+0.5f, -0.5f, -0.5f,	1.0f, 0.0f,		+0.5f, 0.0f, 0.0f,
	+0.5f, -0.5f, -0.5f,	1.0f, 0.0f,		+0.5f, 0.0f, 0.0f,
	+0.5f, -0.5f, +0.5f,	0.0f, 0.0f,		+0.5f, 0.0f, 0.0f,
	+0.5f, +0.5f, +0.5f,	0.0f, 1.0f,		+0.5f, 0.0f, 0.0f,

	// Bottom
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,		0.0f, -0.5f, 0.0f,
	+0.5f, -0.5f, -0.5f,	1.0f, 0.0f,		0.0f, -0.5f, 0.0f,
	+0.5f, -0.5f, +0.5f,	1.0f, 1.0f,		0.0f, -0.5f, 0.0f,
	+0.5f, -0.5f, +0.5f,	1.0f, 1.0f,		0.0f, -0.5f, 0.0f,
	-0.5f, -0.5f, +0.5f,	0.0f, 1.0f,		0.0f, -0.5f, 0.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,		0.0f, -0.5f, 0.0f,

	// Top
	-0.5f, +0.5f, -0.5f,	0.0f, 1.0f,		0.0f, +0.5f, 0.0f,
	+0.5f, +0.5f, -0.5f,	1.0f, 1.0f,		0.0f, +0.5f, 0.0f,
	+0.5f, +0.5f, +0.5f,	1.0f, 0.0f,		0.0f, +0.5f, 0.0f,
	+0.5f, +0.5f, +0.5f,	1.0f, 0.0f,		0.0f, +0.5f, 0.0f,
	-0.5f, +0.5f, +0.5f,	0.0f, 0.0f,		0.0f, +0.5f, 0.0f,
	-0.5f, +0.5f, -0.5f,	0.0f, 1.0f,		0.0f, +0.5f, 0.0f
};


int main()
{
	glfwSetFramebufferSizeCallback(window.frame, resizeWindow);
	glfwSetCursorPosCallback(window.frame, mouseMoved);
	glfwSetScrollCallback(window.frame, mouseScrolled);

	// OBJECT

	VertexArray cube;
	VertexBuffer cubeBuffer(vertices, sizeof(vertices));

	cube.SetAttribPointer(POSITION, 3, 8, 0);
	cube.SetAttribPointer(TEXTURE, 2, 8, 3);
	cube.SetAttribPointer(NORMAL, 3, 8, 5);

	mat4 view;
	mat4 projection;

	// Setting up shaders
	Shader objectShader("vertex.shader", "fragment.shader"), lightShader("lightvertex.shader", "lightfragment.shader");

	// Setting up textures
	Texture stones("stones.jpg");
	Texture sun("sun.jpg");
	Texture::Activate(GL_TEXTURE0);
	
	// Loop until the user closes the window
	while (!window.isClosed())
	{
		GLfloat deltaTime = window.prepareFrame();

		// Process player input
		processInput(window.frame, deltaTime);

		// Calculate the view and projection matrix
		view = camera.getViewMatrix();
		projection = mat4::makePerspective(camera.fov, (GLfloat)window.WIDTH / (GLfloat)window.HEIGHT, 0.1f, 100.0f);
		
		// The view matrix and projection matrix are changing dynamically, so we pass these matrices to the shader every frame
		objectShader.use();
		objectShader.setMat4("view", view);
		objectShader.setMat4("projection", projection);
		mat4 model = mat4::makeTranslate(vec3(0.0f, 0.0f, 0.0f)) * mat4::makeRotate(45.0f, vec3(1.0f, 1.0f, 0.0f)) * mat4::makeScale(vec3(1.0f, 1.0f, 1.0f));
		objectShader.setMat4("model", model);
		objectShader.setInt("tex", 0);
		objectShader.setVec3("objectColor", vec3(1.0f, 0.5f, 0.31f));
		objectShader.setVec3("lightColor", vec3(1.0f, 1.0f, 1.0f));

		// Bind cube to draw twice
		cube.Bind();

		// Draw cube #1
		stones.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);

		lightShader.use();
		lightShader.setMat4("view", view);
		lightShader.setMat4("projection", projection);
		model = mat4::makeTranslate(lightPos) * mat4::makeRotate(45.0f, vec3(1.0f, 1.0f, 0.0f)) * mat4::makeScale(vec3(1.0f, 1.0f, 1.0f));
		lightShader.setMat4("model", model);
		lightShader.setInt("sun", 0);

		// Draw cube #2
		sun.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);

		window.finishFrame();
	}

	glfwTerminate();
	return 0;
}

// ---------------------------------------------------------------------------------------------------------
// PLAYER INPUT
// ---------------------------------------------------------------------------------------------------------
GLvoid processInput(GLFWwindow* frame, GLfloat deltaTime)
{
	if (glfwGetKey(frame, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(frame, true);
	}
	if (glfwGetKey(frame, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.processKeyboard(FORWARD, deltaTime);
	}
	if (glfwGetKey(frame, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.processKeyboard(BACKWARD, deltaTime);
	}
	if (glfwGetKey(frame, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.processKeyboard(LEFT, deltaTime);
	}
	if (glfwGetKey(frame, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.processKeyboard(RIGHT, deltaTime);
	}
}

// GLFW: whenever the window size changed (by OS or user resize), this callback function executes
GLvoid resizeWindow(GLFWwindow* frame, GLint width, GLint height)
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

	camera.processMouseMovement(xoffset, yoffset);
}

// GLFW: whenever the mouse scroll wheel scrolls, this callback is called
GLvoid mouseScrolled(GLFWwindow* frame, GLdouble xoffset, GLdouble yoffset)
{
	camera.setFOV((GLfloat)yoffset);
}