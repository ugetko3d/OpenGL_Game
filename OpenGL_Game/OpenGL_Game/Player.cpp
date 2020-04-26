#include "Player.h"

Player::Player()
{

}

// ---------------------------------------------------------------------------------------------------------
// PLAYER INPUT
// ---------------------------------------------------------------------------------------------------------
void Player::movementInput(GLFWwindow* frame, float deltaTime, bool flyingMode)
{
	if (glfwGetKey(frame, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(frame, true);

	//Update movement of player
	if (glfwGetKey(frame, GLFW_KEY_W) == GLFW_PRESS)
	{
		if (glfwGetKey(frame, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			camera.processKeyboard(Camera::Camera_Movement::FORWARD, deltaTime, true, isFlying);
		else
			camera.processKeyboard(Camera::Camera_Movement::FORWARD, deltaTime, false, isFlying);
	}
	if (glfwGetKey(frame, GLFW_KEY_S) == GLFW_PRESS)
	{
		if (glfwGetKey(frame, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			camera.processKeyboard(Camera::Camera_Movement::BACKWARD, deltaTime, true, isFlying);
		else
			camera.processKeyboard(Camera::Camera_Movement::BACKWARD, deltaTime, false, isFlying);
	}
	if (glfwGetKey(frame, GLFW_KEY_A) == GLFW_PRESS)
	{
		if (glfwGetKey(frame, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			camera.processKeyboard(Camera::Camera_Movement::LEFT, deltaTime, true, isFlying);
		else
			camera.processKeyboard(Camera::Camera_Movement::LEFT, deltaTime, false, isFlying);
	}
	if (glfwGetKey(frame, GLFW_KEY_D) == GLFW_PRESS)
	{
		if (glfwGetKey(frame, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			camera.processKeyboard(Camera::Camera_Movement::RIGHT, deltaTime, true, isFlying);
		else
			camera.processKeyboard(Camera::Camera_Movement::RIGHT, deltaTime, false, isFlying);
	}

	updateFlashlight();

	/*if (glfwGetKey(frame, GLFW_KEY_SPACE) == GLFW_PRESS && !isFlying)
	{
		isJumping = true;

	}

	if (isFlying && gravityPlayer != 0)
		gravityPlayer = 0;

	if (gravityPlayer < 100.0f && !isFlying)
	{
		gravityPlayer += 0.1f;
		processPlayerJump(deltaTime, -gravityPlayer);
	}
	else
	{
		gravityPlayer = 0;
	}

	// Jumping
	if (isJumping && !isFlying)
	{
		jumpStrength -= 0.1f;
		processPlayerJump(deltaTime, jumpStrength);
	}

	if (collision(position))
	{
		if (!isFlying)
		{
			jumpStrength = 7.0f;
			isJumping = false;
		}
	}

	// Set player position in front of camera
	position = vec3(camera.position.x, camera.position.y - 1.0f, camera.position.z + 5.0f);*/
}

// Updates the position and direction of flash light whenever the camera is updated
void Player::updateFlashlight()
{
	flashLight.position = camera.position;
	flashLight.direction = camera.front;
}

//Processing movement for y direction
void Player::processPlayerJump(float deltaTime, float jumpStrength)
{
	float velocity = jumpStrength * deltaTime;
	camera.position = camera.position + vec3(0.0f, velocity, 0.0f);
	updateFlashlight();
}

bool Player::collision(const vec3& objectPos)
{
	// TODO
	return false;
}

void Player::mouseMoved(double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = (float)(xpos - lastX);
	float yoffset;

	if (invertedMouse)
		yoffset = (float)(ypos - lastY); // Inverted mouse controls
	else
		yoffset = (float)(lastY - ypos); // Not inverted mouse controls

	lastX = xpos;
	lastY = ypos;

	camera.processMouseMovement(xoffset, yoffset);
	updateFlashlight();
}

void Player::mouseScrolled(double yoffset)
{
	camera.setFOV((float)yoffset);
	updateFlashlight();
}

void Player::keyPressed(int key, int action)
{
	if (key == GLFW_KEY_F && action == GLFW_PRESS)
	{
		if (flashLight.isEnabled())
			flashLight.disable();
		else
			flashLight.enable();
	}

	if (key == GLFW_KEY_I && action == GLFW_PRESS)
		invertedMouse = !invertedMouse;
}

