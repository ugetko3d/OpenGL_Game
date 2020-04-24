#pragma once
#include <glfw3.h>
#include <iostream>

#include "Camera.h"


class Player {

public:

	int mass = 70;
	vec3 position;
	vec3 hitbox = vec3();

	// Keyboard
	bool isJumping = false;
	bool isFlying = true;
	bool interactWithEntity = false;

	// Mouse
	bool firstMouse = true;
	double lastX;
	double lastY;

	Player(double width, double height);
	Camera& camera = Camera::instance();

	void keyboardInput(GLFWwindow* window, float deltaTime, bool flyingMode);
	void mouseMoved(double xpos, double ypos);
	void mouseScrolled(double yoffset);

private:
	float jumpStrength = 7.0f;
	float gravityPlayer = 0.0f;

	void processPlayerJump(float deltaTime, float jumpStrength);
	bool collision(const vec3& objectPos);

};