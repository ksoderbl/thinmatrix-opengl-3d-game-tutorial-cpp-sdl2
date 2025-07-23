#ifndef PARTICLE_H
#define PARTICLE_H

#include "../Headers.h"
#include "../models/RawModel.h"
#include "../renderEngine/Loader.h"
#include "../textures/TextureData.h"
#include "../entities/Camera.h"
#include "ParticleTexture.h"

class Particle {
public:
	Particle(ParticleTexture* texture,  glm::vec3& position, glm::vec3& velocity, GLfloat gravityEffect,
		 GLfloat lifeLength, GLfloat rotation, GLfloat scale);

	// used with std::sort
	bool operator < (const Particle& r);

	ParticleTexture* getTexture() {
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
	GLfloat getDistance() {
		return distance;
	}
	glm::vec2& getTexOffset1() {
		return texOffset1;
	}
	glm::vec2& getTexOffset2() {
		return texOffset2;
	}
	GLfloat getBlend() {
		return blend;
	}
	bool update(Camera& camera);

private:
	glm::vec3 position;
	glm::vec3 velocity;
	GLfloat gravityEffect; // <= 1.0
	GLfloat lifeLength;
	GLfloat rotation;
	GLfloat scale;
	GLfloat elapsedTime = 0.0f;
	GLfloat distance;

	ParticleTexture* texture;

	glm::vec2 texOffset1;
	glm::vec2 texOffset2;
	GLfloat blend;

	void updateTextureCoordInfo();
	void setTextureOffset(glm::vec2& offset, int index);
};

#endif
