#include "ParticleSystem.h"
#include "Particle.h"
#include "../DisplayManager.h"
#include "../Utils.h"

ParticleSystem::ParticleSystem(GLfloat pps, GLfloat speed, GLfloat gravityCompliant, GLfloat lifeLength)
{
	this->pps = pps;
	this->speed = speed;
	this->gravityCompliant = gravityCompliant;
	this->lifeLength = lifeLength;
}

void ParticleSystem::generateParticles(glm::vec3& systemCenter)
{
	GLfloat delta = display.getFrameTimeSeconds();
	GLfloat particlesToCreate = pps * delta;
	int count = floor(particlesToCreate);
	GLfloat partialParticle = particlesToCreate - (GLfloat)count;
	for (int i = 0; i < count; i++) {
		emitParticle(systemCenter);
	}
	if (Utils::Rand() < partialParticle) {
		emitParticle(systemCenter);
	}
}

void ParticleSystem::emitParticle(glm::vec3& center)
{
	GLfloat dirX = Utils::Rand() * 2.0 - 1.0;
	GLfloat dirZ = Utils::Rand() * 2.0 - 1.0;
	glm::vec3 velocity(dirX, 1, dirZ);
	velocity = glm::normalize(velocity);
	velocity = (GLfloat)speed * velocity;
	Particle particle(center, velocity, 1, 2.5, 0, 1);
}
