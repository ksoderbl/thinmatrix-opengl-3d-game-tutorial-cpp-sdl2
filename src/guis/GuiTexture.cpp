#include "GuiTexture.h"

GuiTexture::GuiTexture(GLuint textureID, glm::vec2& position, glm::vec2& scale)
{
	this->textureID = textureID;
	this->position = position;
	this->scale = scale;
}

GLuint GuiTexture::getTextureId()
{
	return this->textureID;
}

glm::vec2& GuiTexture::getPosition()
{
	return this->position;
}

glm::vec2& GuiTexture::getScale()
{
	return this->scale;
}
