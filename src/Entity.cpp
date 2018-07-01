#include "Entity.h"

Entity::Entity(	TexturedModel &model,
	glm::vec3 position,
	GLfloat rotX, GLfloat rotY, GLfloat rotZ,
	GLfloat scale) : model(model), position(position)
{
	this->rotX = rotX;
	this->rotY = rotY;
	this->rotZ = rotZ;
	this->scale = scale;
}

Entity::Entity(	TexturedModel &model,
	glm::vec3 position,
	int textureIndex,
	GLfloat rotX, GLfloat rotY, GLfloat rotZ,
	GLfloat scale) : model(model), position(position)
{
	this->textureIndex = textureIndex;
	this->rotX = rotX;
	this->rotY = rotY;
	this->rotZ = rotZ;
	this->scale = scale;
}

GLfloat Entity::getTextureXOffset()
{
	int rows = model.getTexture().getNumberOfRows();
	int column = textureIndex % rows;
	return (GLfloat)column/(GLfloat)rows;
}

GLfloat Entity::getTextureYOffset()
{
	int rows = model.getTexture().getNumberOfRows();
	int row = textureIndex / rows;
	return (GLfloat)row/(GLfloat)rows;
}


void Entity::increasePosition(GLfloat dx, GLfloat dy, GLfloat dz)
{
	this->position[0] += dx;
	this->position[1] += dy;
	this->position[2] += dz;
}

void Entity::increaseRotation(GLfloat dx, GLfloat dy, GLfloat dz)
{
	this->rotX += dx;
	this->rotY += dy;
	this->rotZ += dz;
}
