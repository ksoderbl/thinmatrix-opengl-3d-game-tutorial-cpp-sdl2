#include "ParticleSystem.h"
#include "Particle.h"
#include "../DisplayManager.h"
#include "../Utils.h"

ParticleSystem::ParticleSystem(GLfloat pps, GLfloat speed, GLfloat gravityCompliant, GLfloat lifeLength, GLfloat scale)
{
	this->pps = pps;
	this->averageSpeed = speed;
	this->gravityCompliant = gravityCompliant;
	this->averageLifeLength = lifeLength;
	this->averageScale = scale;
}

/**
 * @param direction - The average direction in which particles are emitted.
 * @param deviation - A value between 0 and 1 indicating how far from the chosen direction particles can deviate.
 */
void ParticleSystem::setDirection(glm::vec3 direction, GLfloat deviation)
{
	this->direction = direction;
	this->haveDirection = true;
	this->directionDeviation = deviation;
}

void ParticleSystem::randomizeRotation()
{
	randomRotation = true;
}

void ParticleSystem::generateParticles(glm::vec3 systemCenter)
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
	//GLfloat dirX = Utils::Rand() * 2.0 - 1.0;
	//GLfloat dirZ = Utils::Rand() * 2.0 - 1.0;
	//glm::vec3 velocity(dirX, 1, dirZ);
	glm::vec3 velocity;
	if (haveDirection) {
		velocity = generateRandomUnitVectorWithinCone(direction, directionDeviation);
	} else {
		velocity = generateRandomUnitVector();
	}
	velocity = glm::normalize(velocity);

	GLfloat speed = generateValue(averageSpeed, speedError);
	velocity *= speed;
	GLfloat scale = generateValue(averageScale, scaleError);
	GLfloat lifeLength = generateValue(averageLifeLength, lifeError);

	Particle particle(center, velocity, gravityCompliant, lifeLength, generateRotation(), scale);
}

GLfloat ParticleSystem::generateValue(GLfloat average, GLfloat errorMargin)
{
	GLfloat offset = (Utils::Rand() - 0.5) * 2 * errorMargin;
	return average + offset;
}

GLfloat ParticleSystem::generateRotation()
{
	if (randomRotation) {
		return Utils::Rand() * 360;
	} else {
		return 0;
	}
}

glm::vec3 ParticleSystem::generateRandomUnitVectorWithinCone(glm::vec3& coneDirection, GLfloat angle)
{
	GLfloat cosAngle = cos(angle);
	GLfloat theta = Utils::Rand() * 2 * M_PI;
	GLfloat z = cosAngle + Utils::Rand() * (1 - cosAngle);
	GLfloat rootOneMinusZSquared = sqrt(1 - z * z);
	GLfloat x = rootOneMinusZSquared * cos(theta);
	GLfloat y = rootOneMinusZSquared * sin(theta);

	glm::vec4 direction(x, y, z, 1);

	if (coneDirection.x != 0 || coneDirection.y != 0 || (coneDirection.z != 1 && coneDirection.z != -1)) {
		glm::vec3 k(0, 0, 1);
		glm::vec3 rotateAxis = glm::cross(coneDirection, k);
		rotateAxis = glm::normalize(rotateAxis);
		GLfloat value = glm::dot(coneDirection, k);
		GLfloat rotateAngle = acos(value);
		glm::mat4 unit = glm::mat4(1.0f);
		glm::mat4 rotationMatrix = glm::rotate(unit, -rotateAngle, rotateAxis);
		direction = rotationMatrix * direction;
	} else if (coneDirection.z == -1) {
		direction.z *= -1;
	}

	return glm::vec3(direction.x, direction.y, direction.z);
}

glm::vec3 ParticleSystem::generateRandomUnitVector()
{
	GLfloat theta = Utils::Rand() * 2 * M_PI;
	GLfloat z = Utils::Rand() * 2 - 1;
	GLfloat rootOneMinusZSquared = sqrt(1 - z * z);
	GLfloat x = rootOneMinusZSquared * cos(theta);
	GLfloat y = rootOneMinusZSquared * sin(theta);
	return glm::vec3(x, y, z);
}
