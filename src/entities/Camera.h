#ifndef CAMERA_H
#define CAMERA_H

#include "../Headers.h"
#include "../Keyboard.h"
#include "../entities/Player.h"
#include "../Mouse.h"

class Camera {
public:
	static constexpr GLfloat MIN_DISTANCE_FROM_PLAYER = 5;
	static constexpr GLfloat MAX_DISTANCE_FROM_PLAYER = 1000;
	static constexpr GLfloat MIN_PITCH = 0;
	static constexpr GLfloat MAX_PITCH = 90 - MIN_PITCH;
	static constexpr GLfloat CAMERA_Y_OFFSET = 7;
	static constexpr GLfloat CAMERA_PITCH_OFFSET = 0; // ThinMatrix has 4
	static constexpr GLfloat ZOOM_LEVEL_FACTOR = 10.0f;
	static constexpr GLfloat PITCH_CHANGE_FACTOR = 0.3f;

	Camera(Player& player);
	void move();
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
