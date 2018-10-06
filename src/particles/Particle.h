#ifndef PARTICLE_H
#define PARTICLE_H

#include "../Headers.h"
#include "../models/RawModel.h"
#include "../renderEngine/Loader.h"
#include "../TextureData.h"
#include "ParticleTexture.h"

class Particle {
public:
	Particle(ParticleTexture& texture,  glm::vec3& position, glm::vec3& velocity, GLfloat gravityEffect,
		 GLfloat lifeLength, GLfloat rotation, GLfloat scale);
	ParticleTexture& getTexture() {
		return texture;
	}
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

	ParticleTexture texture;
};

#endif
