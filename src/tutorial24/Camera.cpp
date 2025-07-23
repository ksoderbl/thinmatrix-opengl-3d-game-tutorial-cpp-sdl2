
#include "Camera.h"

Camera::Camera(Player& player) : player(player)
{
	position = glm::vec3(0, 0, 0);
	pitch = 20.0f;
	yaw = 0.0f;
	roll = 0.0f;
	distanceFromPlayer = 100;
	angleAroundPlayer = 0;
}

void Camera::move(Keyboard& keyboard, Mouse& mouse)
{
	calculateZoom(mouse);
	calculatePitch(mouse);
	calculateAngleAroundPlayer(mouse);
	GLfloat horizontalDistance = calculateHorizontalDistance();
	GLfloat verticalDistance = calculateVerticalDistance();
	calculateCameraPosition(horizontalDistance, verticalDistance);
	yaw = 180 - (player.getRotY() + angleAroundPlayer);
	/*
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
	*/
}

void Camera::calculateCameraPosition(GLfloat horizDistance, GLfloat verticDistance)
{
	GLfloat theta = player.getRotY() + angleAroundPlayer;
	GLfloat offsetX = horizDistance * sin(glm::radians(theta));
	GLfloat offsetZ = horizDistance * cos(glm::radians(theta));
	position.x = player.getPosition().x - offsetX;
	position.z = player.getPosition().z - offsetZ;
	position.y = player.getPosition().y + verticDistance;
}

GLfloat Camera::calculateHorizontalDistance()
{
	return distanceFromPlayer * cos(glm::radians(pitch));
}

GLfloat Camera::calculateVerticalDistance()
{
	return distanceFromPlayer * sin(glm::radians(pitch));
}

void Camera::calculateZoom(Mouse& mouse)
{
	GLfloat factor = 5.0f;
	GLfloat zoomLevel = mouse.getDWheel() * factor;
	distanceFromPlayer -= zoomLevel;
	if (distanceFromPlayer < 10) {
		distanceFromPlayer = 10;
	}
}

void Camera::calculatePitch(Mouse& mouse)
{
	GLfloat factor = 0.3f;
	if (mouse.isRightButtonDown()) {
		GLfloat pitchChange = mouse.getDY() * factor;
		pitch += pitchChange;
	}
}

void Camera::calculateAngleAroundPlayer(Mouse& mouse)
{
	GLfloat factor = 0.3f;
	if (mouse.isLeftButtonDown()) {
		GLfloat angleChange = mouse.getDX() * factor;
		angleAroundPlayer -= angleChange;
	}
}
