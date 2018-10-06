#include "ParticleTexture.h"

ParticleTexture::ParticleTexture(GLuint textureID, int numberOfRows)
{
        this->textureID = textureID;
	this->numberOfRows = numberOfRows;
}

GLuint ParticleTexture::getTextureId()
{
        return this->textureID;
}

int ParticleTexture::getNumberOfRows()
{
        return this->numberOfRows;
}
