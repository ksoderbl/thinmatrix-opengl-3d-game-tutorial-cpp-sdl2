#include "TerrainTexture.h"

TerrainTexture::TerrainTexture(GLuint textureID)
{
	this->textureID = textureID;
}

GLuint TerrainTexture::getTextureId()
{
	return this->textureID;
}
