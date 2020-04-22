#include <glew.h>
#include <glfw3.h>

#include "camera.h"

Camera::Camera()
{
	position = POSITION;
	front = FRONT;
	yaw = YAW;
	pitch = PITCH;
	movementSpeed = SPEED;
	mouseSensitivity = SENSITIVITY;
	fov = FOV;

	updateCameraVectors();
}

void Camera::processKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = movementSpeed * deltaTime;
	if (direction == Camera_Movement::FORWARD)
		position = position + (front * velocity);
	if (direction == Camera_Movement::BACKWARD)
		position = position - (front * velocity);
	if (direction == Camera_Movement::LEFT)
		position = position - (right * velocity);
	if (direction == Camera_Movement::RIGHT)
		position = position + (right * velocity);
}

void Camera::processMouseMovement(float xoffset, float yoffset)
{
	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}		

	// Update front, right and up vectors using the updated Eular angles
	updateCameraVectors();
}

void Camera::setFOV(float yoffset)
{
	if (fov >= 1.0f && fov <= 45.0f)
	{
		fov -= yoffset;
	}	
	if (fov <= 1.0f)
	{
		fov = 1.0f;
	}	
	if (fov >= 45.0f)
	{
		fov = 45.0f;
	}	
}

// Set camera position
void Camera::setCameraPosition(vec3 pos)
{
	position = pos;
}

void Camera::updateCameraVectors()
{
	float y = (float)(yaw * (M_PI / 180.0f));
	float p = (float)(pitch * (M_PI / 180.0f));

	// Calculate the new front vector
	front = vec3(cos(y) * cos(p), sin(p), sin(y) * cos(p));
	front.normalize();

	// Also re-calculate the right and up vector
	// Normalize the vectors, because their length gets closer to 0,
	// the more you look up or down which results in slower movement
	right = vec3::cross(front, WORLD_UP);
	right.normalize();
	up = vec3::cross(right, front);
	up.normalize();
}