#include "Particle.h"
#include "ParticleMaster.h"
#include "../Player.h"
#include "../Maths.h"
#include "../DisplayManager.h"

Particle::Particle(glm::vec3& position, glm::vec3& velocity, GLfloat gravityEffect,
		   GLfloat lifeLength, GLfloat rotation, GLfloat scale)
{
	this->position = position;
	this->velocity = velocity;
	this->gravityEffect = gravityEffect;
	this->lifeLength = lifeLength;
	this->rotation = rotation;
	this->scale = scale;
	particleMaster.addParticle(*this);
}

bool Particle::update()
{
	velocity.y += Player::GRAVITY * gravityEffect * display.getFrameTimeSeconds();
	glm::vec3 change(velocity);
	change *= display.getFrameTimeSeconds();
	position += change;
	elapsedTime += display.getFrameTimeSeconds();
	return elapsedTime < lifeLength;
}
