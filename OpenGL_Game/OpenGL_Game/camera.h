#pragma once

#include <glew.h>
#include "maths.h"

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 5.0f;
const GLfloat SENSITIVTY = 0.1f;
const GLfloat FOV = 45.0f;

// An abstract camera class that processes input and calculates the corresponding Eular Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
	// Camera attributes
	vec3 Position;
	vec3 Front;
	vec3 Up;
	vec3 Right;
	const vec3 WORLD_UP = vec3(0.0f, 1.0f, 0.0f);

	// Eular angles
	GLdouble Yaw;
	GLdouble Pitch;

	// Camera options
	GLfloat MovementSpeed;
	GLfloat MouseSensitivity;
	GLfloat Fov;

	// Constructor
	Camera(vec3 eye);

	// Returns the view matrix calculated using Eular angles
	mat4 GetViewMatrix();
	
	// Processes movement input
	GLvoid ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);

	// Set camera position
	GLvoid SetCameraPosition(vec3 v);

	// Processes aim input
	GLvoid ProcessMouseMovement(GLdouble xoffset, GLdouble yoffset);
	
	// Processes zoom input
	GLvoid setFOV(GLfloat yoffset);

private:
	// Calculates the front vector from the Camera's (updated) Eular angles
	GLvoid updateCameraVectors();
};