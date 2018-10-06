#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "../Headers.h"

class ParticleSystem {
public:
	ParticleSystem(GLfloat pps, GLfloat speed, GLfloat gravityCompliant, GLfloat lifeLength);
	void generateParticles(glm::vec3& systemCenter);
	void emitParticle(glm::vec3& center);
private:
	GLfloat pps;
	GLfloat speed;
	GLfloat gravityCompliant;
	GLfloat lifeLength;
};

#endif
