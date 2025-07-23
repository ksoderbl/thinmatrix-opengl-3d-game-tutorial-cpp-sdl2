#include "ParticleTexture.h"

ParticleTexture::ParticleTexture(GLuint textureID, int numberOfRows, bool additive)
{
	this->textureID = textureID;
	this->numberOfRows = numberOfRows;
	this->additive = additive;
}

GLuint ParticleTexture::getTextureId()
{
	return this->textureID;
}

int ParticleTexture::getNumberOfRows()
{
	return this->numberOfRows;
}

bool ParticleTexture::usesAdditiveBlending()
{
	return this->additive;
}
