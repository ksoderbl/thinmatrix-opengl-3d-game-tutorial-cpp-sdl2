
#include "Camera.h"

Camera::Camera()
{
	this->position = glm::vec3(0, 20, 0);
	this->pitch = 7.0f;
	this->yaw = 140.0f;
	this->roll = 0.0f;
}

void Camera::move(Keyboard &keyboard)
{
	if (keyboard.isKeyDown(SDLK_w)) {
		position.z -= 1.0f;
	}
	if (keyboard.isKeyDown(SDLK_d)) {
		position.x += 1.0f;
	}
	if (keyboard.isKeyDown(SDLK_a)) {
		position.x -= 1.0f;
	}
	
	if (keyboard.isKeyDown(SDLK_UP)) {
		pitch += 1.0f;
		//cout << "pitch : " << pitch << endl;
	}
	if (keyboard.isKeyDown(SDLK_DOWN)) {
		pitch -= 1.0f;
		//cout << "pitch : " << pitch << endl;
	}
	if (keyboard.isKeyDown(SDLK_LEFT)) {
		yaw -= 1.0f;
		//cout << "yaw : " << yaw << endl;
	}
	if (keyboard.isKeyDown(SDLK_RIGHT)) {
		yaw += 1.0f;
		//cout << "yaw : " << yaw << endl;
	}
	
}
