#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "../Headers.h"
#include "ParticleTexture.h"

class ParticleSystem {
public:
	ParticleSystem(ParticleTexture& texture, GLfloat pps, GLfloat speed, GLfloat gravityCompliant, GLfloat lifeLength, GLfloat scale);
	void setDirection(glm::vec3 direction, GLfloat deviation);
	void randomizeRotation();
	/**
	 * @param error
	 *            - A number between 0 and 1, where 0 means no error margin.
	 */
	void setSpeedError(GLfloat error) { this->speedError = error * averageSpeed; }

	/**
	 * @param error
	 *            - A number between 0 and 1, where 0 means no error margin.
	 */
	void setLifeError(GLfloat error) { this->lifeError = error * averageLifeLength; }

	/**
	 * @param error
	 *            - A number between 0 and 1, where 0 means no error margin.
	 */
	void setScaleError(float error) { this->scaleError = error * averageScale; }
	void generateParticles(glm::vec3 systemCenter);
	void emitParticle(glm::vec3& center);
	GLfloat generateValue(GLfloat average, GLfloat errorMargin);
	GLfloat generateRotation();
	glm::vec3 generateRandomUnitVectorWithinCone(glm::vec3& coneDirection, GLfloat angle);
	glm::vec3 generateRandomUnitVector();
private:
	ParticleTexture& texture;
	GLfloat pps;
	GLfloat averageSpeed;
	GLfloat gravityCompliant;
	GLfloat averageLifeLength;
	GLfloat averageScale;

	GLfloat speedError;
	GLfloat lifeError;
	GLfloat scaleError = 0;
	bool randomRotation = false;
	glm::vec3 direction;
	bool haveDirection = false;
	GLfloat directionDeviation = 0;
};

#endif
