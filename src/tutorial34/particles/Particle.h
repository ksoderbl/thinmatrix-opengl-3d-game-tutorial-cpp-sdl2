#ifndef PARTICLE_H
#define PARTICLE_H

#include "../Headers.h"
#include "../models/RawModel.h"
#include "../Loader.h"
#include "../TextureData.h"

class Particle {
public:
	Particle(glm::vec3& position, glm::vec3& velocity, GLfloat gravityEffect,
		 GLfloat lifeLength, GLfloat rotation, GLfloat scale);
	glm::vec3& getPosition() {
		return position;
	}
	glm::vec3& getVelocity() {
		return velocity;
	}
	GLfloat getRotation() {
		return rotation;
	}
	GLfloat getScale() {
		return scale;
	}
	bool update();

private:
	glm::vec3 position;
	glm::vec3 velocity;
	GLfloat gravityEffect; // <= 1.0
	GLfloat lifeLength;
	GLfloat rotation;
	GLfloat scale;
	GLfloat elapsedTime = 0.0f;
};

#endif
