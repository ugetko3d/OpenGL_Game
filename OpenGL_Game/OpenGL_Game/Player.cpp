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

	updateAttributes();

}

// Updates the position and direction of flash light whenever the camera is updated
// Also updates the player's hitbox position
void Player::updateAttributes()
{
	flashLight.position = camera.position;
	flashLight.direction = camera.front;

	hitbox.position = camera.position;
}

//Processing movement for y direction
void Player::processPlayerJump(float deltaTime, float jumpStrength)
{
	float velocity = jumpStrength * deltaTime;
	camera.position = camera.position + vec3(0.0f, velocity, 0.0f);
	updateAttributes();
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
	updateAttributes();
}

void Player::mouseScrolled(double yoffset)
{
	camera.setFOV((float)yoffset);
	updateAttributes();
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

