#include "WaterTile.h"

WaterTile::WaterTile(GLfloat centerX, GLfloat centerZ, GLfloat height, GLfloat scale)
{
	this->x = centerX;
	this->z = centerZ;
	this->height = height;
	this->scale = scale;
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

GLfloat WaterTile::getScale()
{
	return scale;
}
