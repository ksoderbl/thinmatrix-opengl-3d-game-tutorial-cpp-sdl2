#ifndef CAMERA_H
#define CAMERA_H

#include "Headers.h"

class Camera {
public:
	glm::vec3& getPosition() { return position; }
	GLfloat getPitch() { return pitch; }
	GLfloat getYaw() { return yaw; }
	GLfloat getRoll() { return roll; }
private:
	glm::vec3 position;
	GLfloat pitch;
	GLfloat yaw;
	GLfloat roll;
};

#endif
