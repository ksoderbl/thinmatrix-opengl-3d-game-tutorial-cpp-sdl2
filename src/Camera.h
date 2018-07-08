#ifndef CAMERA_H
#define CAMERA_H

#include "Headers.h"
#include "Keyboard.h"
#include "Player.h"
#include "Mouse.h"

class Camera {
public:
	Camera(Player& player);
	void move(Keyboard& keyboard, Mouse& mouse);
	glm::vec3& getPosition() { return position; }
	GLfloat getPitch() { return pitch; }
	GLfloat getYaw() { return yaw; }
	GLfloat getRoll() { return roll; }
	void invertPitch() { pitch = -pitch; }
private:
	void calculateCameraPosition(GLfloat horizDistance, GLfloat verticDistance);
	GLfloat calculateHorizontalDistance();
	GLfloat calculateVerticalDistance();
	void calculateZoom(Mouse& mouse);
	void calculatePitch(Mouse& mouse);
	void calculateAngleAroundPlayer(Mouse& mouse);

	Player& player;
	GLfloat distanceFromPlayer;
	GLfloat angleAroundPlayer;

	glm::vec3 position;
	GLfloat pitch;
	GLfloat yaw;
	GLfloat roll;
};

#endif
