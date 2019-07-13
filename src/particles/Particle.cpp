#include "Particle.h"
#include "ParticleMaster.h"
#include "../entities/Player.h"
#include "../toolbox/Maths.h"
#include "../renderEngine/DisplayManager.h"

Particle::Particle(ParticleTexture* texture, glm::vec3& position, glm::vec3& velocity, GLfloat gravityEffect,
		   GLfloat lifeLength, GLfloat rotation, GLfloat scale)
{
	this->texture = texture;
	this->position = position;
	this->velocity = velocity;
	this->gravityEffect = gravityEffect;
	this->lifeLength = lifeLength;
	this->rotation = rotation;
	this->scale = scale;
	particleMaster.addParticle(*this);
}

bool Particle::operator < (const Particle& r) const
{
	return this->distance > r.distance;
}

bool Particle::update(Camera& camera)
{
	velocity.y += Player::GRAVITY * gravityEffect * display.getFrameTimeSeconds();
	glm::vec3 change(velocity);
	change *= display.getFrameTimeSeconds();
	position += change;
	glm::vec3 d = camera.getPosition() - position;
	distance = d.x * d.x + d.y * d.y + d.z * d.z; // length squared
	updateTextureCoordInfo();
	elapsedTime += display.getFrameTimeSeconds();
	return elapsedTime < lifeLength;
}

void Particle::updateTextureCoordInfo()
{
	GLfloat lifeFactor = elapsedTime / lifeLength;
	int stageCount = texture->getNumberOfRows() * texture->getNumberOfRows();
	GLfloat atlasProgression = lifeFactor * stageCount;
	int index1 = (int) floor(atlasProgression);
	int index2 = index1 < stageCount - 1 ? index1 + 1 : index1;
	this->blend = atlasProgression - (GLfloat) index1;

	setTextureOffset(texOffset1, index1);
	setTextureOffset(texOffset2, index2);
}

void Particle::setTextureOffset(glm::vec2& offset, int index)
{
	int column = index % texture->getNumberOfRows();
	int row = index / texture->getNumberOfRows();
	offset.x = (GLfloat)column / texture->getNumberOfRows();
	offset.y = (GLfloat)row / texture->getNumberOfRows();
}
