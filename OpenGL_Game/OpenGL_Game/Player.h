#pragma once
#include <glfw3.h>
#include <iostream>

#include "Camera.h"
#include "SpotLight.h"


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
	bool invertedMouse = false;
	double lastX;
	double lastY;

	Player();

	Camera& camera = Camera::instance();
	SpotLight flashLight = SpotLight(vec3(0.8f, 0.8f, 0.1f), camera.position, camera.front);

	void movementInput(GLFWwindow* window, float deltaTime, bool flyingMode);
	void mouseMoved(double xpos, double ypos);
	void mouseScrolled(double yoffset);
	void keyPressed(int key, int action);

private:
	float jumpStrength = 7.0f;
	float gravityPlayer = 0.0f;

	void updateFlashlight();
	void processPlayerJump(float deltaTime, float jumpStrength);
	bool collision(const vec3& objectPos);

};