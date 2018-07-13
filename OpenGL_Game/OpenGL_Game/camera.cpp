#include "camera.h"

Camera::Camera(vec3 eye)
{
	Position = eye;
	Front = vec3(0.0f, 0.0f, -1.0f);

	Yaw = YAW;
	Pitch = PITCH;

	MovementSpeed = SPEED;
	MouseSensitivity = SENSITIVTY;
	Fov = FOV;

	updateCameraVectors();
}

mat4 Camera::GetViewMatrix()
{
	vec3 Center(vec3::add(Position, Front));
	vec3 f(vec3::normalize(vec3::subtract(Center, Position)));
	vec3 s(vec3::normalize(vec3::cross(f, Up)));
	vec3 u(vec3::cross(s, f));

	mat4 result;

	result.matrix[0] = s.x;
	result.matrix[4] = s.y;
	result.matrix[8] = s.z;
	result.matrix[1] = u.x;
	result.matrix[5] = u.y;
	result.matrix[9] = u.z;
	result.matrix[2] = -f.x;
	result.matrix[6] = -f.y;
	result.matrix[10] = -f.z;
	result.matrix[12] = -vec3::dot(s, Position);
	result.matrix[13] = -vec3::dot(u, Position);
	result.matrix[14] = vec3::dot(f, Position);
	result.matrix[15] = 1.0f;

	return result;
}

GLvoid Camera::ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime)
{
	GLfloat velocity = MovementSpeed * deltaTime;
	if (direction == FORWARD)
		Position = vec3::add(Position, vec3::scale(Front, velocity));
	if (direction == BACKWARD)
		Position = vec3::subtract(Position, vec3::scale(Front, velocity));
	if (direction == LEFT)
		Position = vec3::subtract(Position, vec3::scale(Right, velocity));
	if (direction == RIGHT)
		Position = vec3::add(Position, vec3::scale(Right, velocity));
}

GLvoid Camera::ProcessMouseMovement(GLdouble xoffset, GLdouble yoffset)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped

	if (Pitch > 89.0f)
		Pitch = 89.0f;
	if (Pitch < -89.0f)
		Pitch = -89.0f;

	// Update Front, Right and Up vectors using the updated Eular angles
	updateCameraVectors();
}

GLvoid Camera::setFOV(GLfloat yoffset)
{
	if (Fov >= 1.0f && Fov <= 45.0f)
		Fov -= yoffset;
	if (Fov <= 1.0f)
		Fov = 1.0f;
	if (Fov >= 45.0f)
		Fov = 45.0f;
}

//Set position camera
GLvoid Camera::SetCameraPosition(vec3 v)
{
	Position = v;
}

GLvoid Camera::updateCameraVectors()
{
	GLfloat y = (GLfloat)(Yaw * (M_PI / 180.0f));
	GLfloat p = (GLfloat)(Pitch * (M_PI / 180.0f));

	// Calculate the new Front vector
	vec3 front(cos(y) * cos(p), sin(p), sin(y) * cos(p));
	Front = vec3::normalize(front);

	// Also re-calculate the Right and Up vector
	Right = vec3::normalize(vec3::cross(Front, WORLD_UP));  // Normalize the vectors, because their length gets closer to 0, 
	Up = vec3::normalize(vec3::cross(Right, Front));		// the more you look up or down which results in slower movement
}