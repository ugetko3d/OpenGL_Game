#include <glew.h>
#include <glfw3.h>

#include "maths.h"

#include "shader.h"
#include "Material.h"
#include "CubeMap.h"

#include "Light.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

#include "Player.h"

#include "Vertex.h"
#include "Cube.h"
#include "Diamond.h"
#include "Sphere.h"
#include "Rectangle.h"

// Window
GLFWwindow* window;
const char* WINDOW_TITLE = "OpenGL Game";
const int OPENGL_MIN = 4, OPENGL_MAX = 4;
unsigned int WINDOW_WIDTH = 1200, WINDOW_HEIGHT = 700;

// Timing
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f;

// Player
Player player;

// Shaders
Shader objectShader, lightShader, cubeMapShader;

// Materials
Material metal, tile, mixedstone;

// Cubemap
CubeMap cubemap;

// Objects
Cube cube(1.0f);
//Diamond diamond(1.0f);
//Diamond diamondPickUp(1.0f);
Sphere sphere(1.0f, 4);
//Sphere sphere_low(1.0f, 1);
//Sphere sphere_medium(1.0f, 2);
//Sphere sphere_high(1.0f, 4);
//Rect rect(1.0f, 1.0f);

// Lights
std::vector<Light> lights;
vec3 sunDirection(0.0, 1.0, 0.0f);
vec3 sunColour(1.0f, 1.0f, 0.5f);
vec3 lightColour(0.8f, 0.8f, 0.1f);

PointLight pointLight(vec3(1.0f), vec3(0.0f, 5.0f, 0.0f));
DirectionalLight directionLight(sunColour, sunDirection);


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
void framebuffer_size_callback(GLFWwindow* frame, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// GLFW: whenever the mouse moves, this callback is called
void mouse_callback(GLFWwindow* frame, double xpos, double ypos)
{
	player.mouseMoved(xpos, ypos);
}

// GLFW: whenever the mouse scroll wheel scrolls, this callback is called
void scroll_callback(GLFWwindow* frame, double xoffset, double yoffset)
{
	player.mouseScrolled(yoffset);
}

void key_callback(GLFWwindow* frame, int key, int scancode, int action, int mods)
{
	player.keyPressed(key, action);
}


/* DRAW OBJECTS - set up shaders and call vertex draw functions */
void renderObjects(const mat4& projection, const mat4& view)
{
	// Activate shader when setting uniforms/drawing objects
	objectShader.use();
	objectShader.setMat4("projection", projection);
	objectShader.setMat4("view", view);
	objectShader.setFloat("material.shininess", 64.0f);
	objectShader.setVec3("viewPos", player.camera.position);

	// lights
	objectShader.setInt("directionLightCount", Light::numDirectionalLights());
	objectShader.setInt("pointLightCount", Light::numPointLights());
	objectShader.setInt("spotLightCount", Light::numSpotLights());
	objectShader.setInt("lightCount", lights.size());

	for (unsigned int i = 0; i < lights.size(); i++)
	{
		objectShader.setVec3("lightPositions[" + std::to_string(i) + "]", lights.at(i).position);
		lights.at(i).drawLight(objectShader);
	}

	player.flashLight.drawLight(objectShader);

	cube.drawObject(objectShader, vec3(0.0f, 0.0f, 5.0f), &metal);

}

void renderLights(mat4 projection, mat4 view)
{
	// Activate light shader and configure it
	lightShader.use();
	lightShader.setMat4("projection", projection);
	lightShader.setMat4("view", view);
	lightShader.setBool("hasLightColour", true);

	// Draw light object
	for (Light l : lights)
	{
		lightShader.setVec3("lightColour", lightColour);
		if (l.is(Light::Type::POINT))
		{
			sphere.drawObject(lightShader, l.position, nullptr);
			l.colour = lightColour;
		}
	}
}

int main()
{
	// Setting up OpenGL
	createDisplay();
	startOpenGL();

	// Enabling interrupts for keyboard/mouse input
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);

	// Set mouse position in the center of the window
	player.lastX = WINDOW_WIDTH / 2.0f;
	player.lastY = WINDOW_HEIGHT / 2.0f;

	// Load shaders
	objectShader.loadShader("shaders/object_vert.shader", "shaders/object_frag.shader");
	lightShader.loadShader("shaders/light_vert.shader", "shaders/light_frag.shader");
	cubeMapShader.loadShader("shaders/cubemap_vert.shader", "shaders/cubemap_frag.shader");

	// Set object shader uniforms
	objectShader.use();
	objectShader.setInt("material.diffuse", 0);
	objectShader.setInt("material.specular", 1);
	objectShader.setInt("material.normal", 2);
	objectShader.setInt("material.displacement", 3);
	objectShader.setInt("material.AO", 4);

	// Set cubemap shader uniforms
	cubeMapShader.use();
	cubeMapShader.setInt("skybox", 0);

	// Store all objects on GPU
	cubemap.storeOnGPU();
	cube.storeOnGPU();
	sphere.storeOnGPU();

	// Load cubemap textures
	cubemap.loadCubemapTexture(
		"resources/skybox/right.jpg",
		"resources/skybox/left.jpg",
		"resources/skybox/top.jpg",
		"resources/skybox/bottom.jpg",
		"resources/skybox/back.jpg",
		"resources/skybox/front.jpg"
	);

	// Load metal textures
	metal.addDiffuse(Texture("resources/textures/1857-diffuse.jpg"));
	metal.addSpecular(Texture("resources/textures/1857-specexponent.jpg"));
	metal.addNormal(Texture("resources/textures/1857-normal.jpg"));
	metal.addDisplacement(Texture("resources/textures/1857-displacement.jpg"));

	// Load tile textures
	tile.addDiffuse(Texture("resources/textures/10744-diffuse.jpg"));
	tile.addSpecular(Texture("resources/textures/10744-specstrength.jpg"));
	tile.addNormal(Texture("resources/textures/10744-normal.jpg"));
	tile.addDisplacement(Texture("resources/textures/10744-displacement.jpg"));

	// Load mixedstone textures
	mixedstone.addDiffuse(Texture("resources/textures/mixedstones-diffuse.jpg"));
	mixedstone.addSpecular(Texture("resources/textures/mixedstones-specular.jpg"));
	mixedstone.addNormal(Texture("resources/textures/mixedstones-normal.jpg"));
	mixedstone.addDisplacement(Texture("resources/textures/mixedstones-displace.jpg"));

	// Add lights to the list
	lights.push_back(pointLight);
	lights.push_back(directionLight);

	mat4 view, projection;

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
		player.movementInput(window, deltaTime, true);

		view.makeView(player.camera.position, player.camera.front, player.camera.up);
		projection.makePerspective(player.camera.fov, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);

		// Render the objects to the screen
		renderObjects(projection, view);

		// Render the lighting to the screen
		renderLights(projection, view);

		// Render the skybox at the end
		cubemap.drawCubemap(cubeMapShader, view, projection);

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
