#pragma once

#include "maths.h"

// An abstract camera class that processes input and calculates the corresponding Eular Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
	// Default camera values
	const vec3 POSITION = vec3(0.0f, 0.0f, 10.0f);
	const vec3 FRONT = vec3(0.0f, 0.0f, 0.0f);
	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	const float SPEED = 8.0f;
	const float SENSITIVITY = 0.1f;
	const float FOV = 45.0f;
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
	double yaw;
	double pitch;

	// Camera options
	float movementSpeed;
	float mouseSensitivity;
	float fov;

	// Deleting the copy constructor (because this class is a singleton)
	Camera(const Camera&) = delete;

	static Camera& instance()
	{
		static Camera instance;
		return instance;
	}

	// Processes movement input
	void processKeyboard(Camera_Movement direction, float deltaTime);

	// Set camera position
	void setCameraPosition(vec3 pos);

	// Processes aim input
	void processMouseMovement(float xoffset, float yoffset);

	// Processes zoom input
	void setFOV(float yoffset);

private:
	// Constructor
	Camera();

	// Calculates the front vector from the Camera's (updated) Eular angles
	void updateCameraVectors();
};