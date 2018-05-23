
#include "Camera.h"

Camera::Camera()
{
	this->position = glm::vec3(0, 0, 0);
	this->pitch = 0.0f;
	this->yaw = 0.0f;
	this->roll = 0.0f;
}

void Camera::move(Keyboard &keyboard)
{
	if (keyboard.isKeyDown(SDLK_w)) {
		position.z -= 0.1f;
	}
	if (keyboard.isKeyDown(SDLK_d)) {
		position.x += 0.1f;
	}
	if (keyboard.isKeyDown(SDLK_a)) {
		position.x -= 0.1f;
	}
}
