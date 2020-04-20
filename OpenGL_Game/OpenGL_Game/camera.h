#pragma once

#include "maths.h"

// An abstract camera class that processes input and calculates the corresponding Eular Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
	// Default camera values
	const vec3 POSITION = vec3(0.0f, 0.0f, 10.0f);
	const vec3 FRONT = vec3(0.0f, 0.0f, 0.0f);
	const GLfloat YAW = -90.0f;
	const GLfloat PITCH = 0.0f;
	const GLfloat SPEED = 8.0f;
	const GLfloat SENSITIVITY = 0.1f;
	const GLfloat FOV = 45.0f;
	const vec3 WORLD_UP = vec3(0.0f, 1.0f, 0.0f);

	// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
	enum class Camera_Movement
	{
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	// Camera attributes
	vec3 position;
	vec3 front;
	vec3 up;
	vec3 right;

	// Eular angles
	GLdouble yaw;
	GLdouble pitch;

	// Camera options
	GLfloat movementSpeed;
	GLfloat mouseSensitivity;
	GLfloat fov;

	// Deleting the copy constructor (because this class is a singleton)
	Camera(const Camera&) = delete;

	static Camera& instance()
	{
		static Camera instance;
		return instance;
	}

	// Returns the view matrix
	mat4& getViewMatrix();

	// Calculates the view matrix
	GLvoid updateViewMatrix();

	// Processes movement input
	GLvoid processKeyboard(Camera_Movement direction, GLfloat deltaTime);

	// Set camera position
	GLvoid setCameraPosition(vec3 pos);

	// Processes aim input
	GLvoid processMouseMovement(GLdouble xoffset, GLdouble yoffset);

	// Processes zoom input
	GLvoid setFOV(GLfloat yoffset);

private:
	// View matrix
	mat4 m_view;

	// Constructor
	Camera();

	// Calculates the front vector from the Camera's (updated) Eular angles
	GLvoid updateCameraVectors();
};