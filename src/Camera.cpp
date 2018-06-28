
#include "Camera.h"

Camera::Camera()
{
	this->position = glm::vec3(0, 20, -50);
	this->pitch = 20.0f;
	this->yaw = 90.0f;
	this->roll = 0.0f;
}

void Camera::move(Keyboard &keyboard)
{
	double angle = glm::radians(yaw);
	double s = 2 * sin(angle);
	double c = 2 * cos(angle);

	if (keyboard.isKeyDown(SDLK_p)) {
		pitch += 2.0f;
		//cout << "pitch : " << pitch << endl;
	}
	if (keyboard.isKeyDown(SDLK_o)) {
		pitch -= 2.0f;
		//cout << "pitch : " << pitch << endl;
	}
	if (keyboard.isKeyDown(SDLK_HOME)) {
		position.x -= c;
		position.z -= s;
	}
	if (keyboard.isKeyDown(SDLK_END)) {
		position.x += c;
		position.z += s;
	}

	if (keyboard.isKeyDown(SDLK_PAGEUP)) {
		position.y += 1.5f;
	}
	if (keyboard.isKeyDown(SDLK_PAGEDOWN)) {
		position.y -= 1.5f;
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
