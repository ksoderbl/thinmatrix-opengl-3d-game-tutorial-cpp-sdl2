#include "WaterTile.h"

WaterTile::WaterTile(GLfloat centerX, GLfloat centerZ, GLfloat height)
{
	this->x = centerX;
	this->z = centerZ;
	this->height = height;
}

GLfloat WaterTile::getHeight()
{
	return height;
}

GLfloat WaterTile::getX()
{
	return x;
}

GLfloat WaterTile::getZ()
{
	return z;
}
