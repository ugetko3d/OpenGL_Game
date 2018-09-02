#pragma once

#include "maths.hpp"

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
const enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 8.0f;
const GLfloat SENSITIVTY = 0.1f;
const GLfloat FOV = 45.0f;
const vec3 WORLD_UP = vec3(0.0f, 1.0f, 0.0f);

// An abstract camera class that processes input and calculates the corresponding Eular Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
	// Camera attributes
	static vec3 position;
	static vec3 front;
	static vec3 up;
	static vec3 right;

	// Eular angles
	static GLdouble yaw;
	static GLdouble pitch;

	// Camera options
	static GLfloat movementSpeed;
	static GLfloat mouseSensitivity;
	static GLfloat fov;

	static GLvoid init();

	// Returns the view matrix calculated using Eular angles
	static mat4 getViewMatrix();

	// Processes movement input
	static GLvoid processKeyboard(Camera_Movement direction, GLfloat deltaTime);

	// Set camera position
	static GLvoid setCameraPosition(vec3 pos);

	// Processes aim input
	static GLvoid processMouseMovement(GLdouble xoffset, GLdouble yoffset);

	// Processes zoom input
	static GLvoid setFOV(GLfloat yoffset);

private:
	// Calculates the front vector from the Camera's (updated) Eular angles
	static GLvoid updateCameraVectors();
};