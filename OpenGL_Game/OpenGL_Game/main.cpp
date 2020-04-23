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
void processInput(GLFWwindow* frame, float deltaTime);
void resizeWindow(GLFWwindow* frame, int width, int height);
void mouseMoved(GLFWwindow* frame, double xpos, double ypos);
void mouseScrolled(GLFWwindow* frame, double xoffset, double yoffset);

const enum attrib
{
	POSITION, TEXTURE, NORMAL
};

// Window
Window window;

// Camera
Camera& camera = Camera::instance();
bool firstMouse = true;
double lastX = (double) (window.WIDTH / 2.0f);
double lastY = (double) (window.HEIGHT / 2.0f);

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

	mat4 t, r, s, model, view, projection;

	// Setting up shaders
	Shader objectShader("vertex.shader", "fragment.shader"), lightShader("lightvertex.shader", "lightfragment.shader");

	// Setting up textures
	Texture stones("stones.jpg");

	// Rotation angle that is used for rotating the objects. Value is increased after every iteration of the renderer loop.
	float angle = 0.0f;
	
	// Loop until the user closes the window
	while (!window.isClosed())
	{
		float deltaTime = window.prepareFrame();

		// Process player input
		processInput(window.frame, deltaTime);

		// Calculate the view and projection matrix
		view.makeView(camera.position, camera.front, camera.up);
		projection.makePerspective(camera.fov, (float)window.WIDTH / (float)window.HEIGHT, 0.1f, 100.0f);
		
		// The view matrix and projection matrix are changing dynamically, so we pass these matrices to the shader every frame
		objectShader.use();
		objectShader.setInt("tex", 0);
		objectShader.setMat4("view", view);
		objectShader.setMat4("projection", projection);
		t.translate(vec3(0.0f, 0.0f, 0.0f));
		r.rotate(angle, vec3(0.3f, 0.5f, 0.6f));
		angle += 0.5f;
		s.scale(vec3(1.0f, 1.0f, 1.0f));
		model = t * r * s;
		objectShader.setMat4("model", model);
		objectShader.setVec3("viewPos", camera.position);
		objectShader.setVec3("lightPos", lightPos);
		objectShader.setVec3("lightColour", vec3(1.0f, 1.0f, 1.0f));

		// Bind cube to draw twice
		cube.Bind();

		// Draw cube #1
		stones.Bind(0);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		stones.Unbind();

		lightShader.use();
		lightShader.setMat4("view", view);
		lightShader.setMat4("projection", projection);
		t.translate(lightPos);
		r.rotate(45.0f, vec3(1.0f, 1.0f, 0.0f));
		s.scale(vec3(1.0f, 1.0f, 1.0f));
		model = t * r * s;
		lightShader.setMat4("model", model);
		lightShader.setInt("sun", 0);

		// Draw cube #2
		glDrawArrays(GL_TRIANGLES, 0, 36);

		window.finishFrame();
	}

	glfwTerminate();
	return 0;
}

// ---------------------------------------------------------------------------------------------------------
// PLAYER INPUT
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* frame, float deltaTime)
{
	if (glfwGetKey(frame, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(frame, true);
	}
	if (glfwGetKey(frame, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.processKeyboard(Camera::Camera_Movement::FORWARD, deltaTime);
	}
	if (glfwGetKey(frame, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.processKeyboard(Camera::Camera_Movement::BACKWARD, deltaTime);
	}
	if (glfwGetKey(frame, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.processKeyboard(Camera::Camera_Movement::LEFT, deltaTime);
	}
	if (glfwGetKey(frame, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.processKeyboard(Camera::Camera_Movement::RIGHT, deltaTime);
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
void mouseMoved(GLFWwindow* frame, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = (float) (xpos - lastX);
	float yoffset = (float) (lastY - ypos); // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.processMouseMovement(xoffset, yoffset);
}

// GLFW: whenever the mouse scroll wheel scrolls, this callback is called
void mouseScrolled(GLFWwindow* frame, double xoffset, double yoffset)
{
	camera.setFOV((float)yoffset);
}