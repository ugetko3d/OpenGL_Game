#include <glew.h>

#include "camera.hpp"

GLvoid Camera::init()
{
	position = vec3(0.0f, 0.0f, -10.0f);
	front = vec3(0.0f, 0.0f, -1.0f);

	yaw = YAW;
	pitch = PITCH;

	movementSpeed = SPEED;
	mouseSensitivity = SENSITIVTY;
	fov = FOV;

	updateCameraVectors();
}

mat4 Camera::getViewMatrix()
{
	vec3 center(vec3::add(position, front));
	vec3 f(vec3::normalize(vec3::subtract(center, position)));
	vec3 s(vec3::normalize(vec3::cross(f, up)));
	vec3 u(vec3::cross(s, f));

	mat4 result;

	result.data[0] = s.x;
	result.data[4] = s.y;
	result.data[8] = s.z;
	result.data[1] = u.x;
	result.data[5] = u.y;
	result.data[9] = u.z;
	result.data[2] = -f.x;
	result.data[6] = -f.y;
	result.data[10] = -f.z;
	result.data[12] = -vec3::dot(s, position);
	result.data[13] = -vec3::dot(u, position);
	result.data[14] = vec3::dot(f, position);
	result.data[15] = 1.0f;

	return result;
}

GLvoid Camera::processKeyboard(Camera_Movement direction, GLfloat deltaTime)
{
	GLfloat velocity = movementSpeed * deltaTime;
	if (direction == FORWARD)
		position = vec3::add(position, vec3::scale(front, velocity));
	if (direction == BACKWARD)
		position = vec3::subtract(position, vec3::scale(front, velocity));
	if (direction == LEFT)
		position = vec3::subtract(position, vec3::scale(right, velocity));
	if (direction == RIGHT)
		position = vec3::add(position, vec3::scale(right, velocity));
}

GLvoid Camera::processMouseMovement(GLdouble xoffset, GLdouble yoffset)
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

GLvoid Camera::setFOV(GLfloat yoffset)
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
GLvoid Camera::setCameraPosition(vec3 pos)
{
	position = pos;
}

GLvoid Camera::updateCameraVectors()
{
	GLfloat y = (GLfloat)(yaw * (M_PI / 180.0f));
	GLfloat p = (GLfloat)(pitch * (M_PI / 180.0f));

	// Calculate the new front vector
	front = vec3::normalize(vec3(cos(y) * cos(p), sin(p), sin(y) * cos(p)));

	// Also re-calculate the right and up vector
	// Normalize the vectors, because their length gets closer to 0,
	// the more you look up or down which results in slower movement
	right = vec3::normalize(vec3::cross(front, WORLD_UP));
	up = vec3::normalize(vec3::cross(right, front));
}