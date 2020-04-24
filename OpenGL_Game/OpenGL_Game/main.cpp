#include <glew.h>
#include <glfw3.h>

#include "maths.h"
#include "shader.h"
#include "texture.h"
#include "Player.h"

#include "vertex_array.h"
#include "vertex_buffer.h"
#include "index_buffer.h"

// Processes input
void resizeWindow(GLFWwindow* frame, int width, int height);
void mouseMoved(GLFWwindow* frame, double xpos, double ypos);
void mouseScrolled(GLFWwindow* frame, double xoffset, double yoffset);

const enum attrib
{
	POSITION, TEXTURE, NORMAL
};

// Window
GLFWwindow* window;
const char* WINDOW_TITLE = "OpenGL Game";
const int OPENGL_MIN = 4, OPENGL_MAX = 4;
unsigned int WINDOW_WIDTH = 1200, WINDOW_HEIGHT = 700;

// Timing
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f;

// Player
Player player((WINDOW_WIDTH / 2.0f), (WINDOW_HEIGHT / 2.0f));

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

// Initialize GLFW (window for OpenGL)
void createDisplay()
{
	// Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAX);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MIN);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	// Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
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

// Initialize OpenGL
void startOpenGL()
{
	glewExperimental = true;

	// Initialize GLEW
	unsigned int glewStatus = glewInit();

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
	player.mouseMoved(xpos, ypos);
}

// GLFW: whenever the mouse scroll wheel scrolls, this callback is called
void mouseScrolled(GLFWwindow* frame, double xoffset, double yoffset)
{
	player.mouseScrolled(yoffset);
}

int main()
{
	createDisplay();
	startOpenGL();

	glfwSetFramebufferSizeCallback(window, resizeWindow);
	glfwSetCursorPosCallback(window, mouseMoved);
	glfwSetScrollCallback(window, mouseScrolled);

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
	while (!glfwWindowShouldClose(window))
	{

		// Per-frame time logic
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Process player input (mouse input is handled automatically by GLFW)
		player.keyboardInput(window, deltaTime, true);

		// Calculate the view and projection matrix
		view.makeView(player.camera.position, player.camera.front, player.camera.up);
		projection.makePerspective(player.camera.fov, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);

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
		objectShader.setVec3("viewPos", player.camera.position);
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

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
