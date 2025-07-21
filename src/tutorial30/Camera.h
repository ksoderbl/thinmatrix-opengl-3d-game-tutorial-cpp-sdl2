#ifndef CAMERA_H
#define CAMERA_H

#include "Headers.h"
#include "Keyboard.h"
#include "Player.h"
#include "Mouse.h"

class Camera {
public:
    static constexpr GLfloat MIN_DISTANCE_FROM_PLAYER = 5;
    static constexpr GLfloat MAX_DISTANCE_FROM_PLAYER = 1000;
    static constexpr GLfloat MIN_PITCH = 1;
    static constexpr GLfloat MAX_PITCH = 90 - MIN_PITCH;
    static constexpr GLfloat CAMERA_Y_OFFSET = 7;

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
