
#include "Camera.h"

Camera::Camera()
{
	this->position = glm::vec3(0, 5.0f, 0);
	this->pitch = 12.0f;
	this->yaw = 0.0f;
	this->roll = 0.0f;
}

void Camera::move(Keyboard &keyboard)
{
	double angle = glm::radians(yaw);
	double s = 2 * sin(angle);
	double c = 2 * cos(angle);

	if (keyboard.isKeyDown(SDLK_w)) {
		pitch += 1.0f;
		//cout << "pitch : " << pitch << endl;
	}
	if (keyboard.isKeyDown(SDLK_s)) {
		pitch -= 1.0f;
		//cout << "pitch : " << pitch << endl;
	}
	if (keyboard.isKeyDown(SDLK_a)) {
		position.x -= c;
		position.z -= s;
	}
	if (keyboard.isKeyDown(SDLK_d)) {
		position.x += c;
		position.z += s;
	}

	if (keyboard.isKeyDown(SDLK_PAGEUP)) {
		position.y += 0.5f;
	}
	if (keyboard.isKeyDown(SDLK_PAGEDOWN)) {
		position.y -= 0.5f;
		if (position.y < 0.1f) {
			position.y = 0.1f;
		}
	}

	if (keyboard.isKeyDown(SDLK_UP)) {
		position.x += s;
		position.z -= c;
	}
	
	if (keyboard.isKeyDown(SDLK_DOWN)) {
		position.x -= s;
		position.z += c;
	}
	
	if (keyboard.isKeyDown(SDLK_LEFT)) {
		yaw -= 2.0f;
	}
	
	if (keyboard.isKeyDown(SDLK_RIGHT)) {
		yaw += 2.0f;
	}
	
}
