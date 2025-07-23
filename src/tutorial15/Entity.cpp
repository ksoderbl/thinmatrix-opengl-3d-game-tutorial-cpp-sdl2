#include "Entity.h"

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
