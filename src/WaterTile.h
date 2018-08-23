#ifndef WATERTILE_H
#define WATERTILE_H

#include "Headers.h"

class WaterTile {
public:
	static constexpr GLfloat TILE_SIZE = 800;
	WaterTile(GLfloat centerX, GLfloat centerZ, GLfloat height);
	GLfloat getHeight();
	GLfloat getX();
	GLfloat getZ();
private:
	GLfloat height;
	GLfloat x, z;
};

#endif
