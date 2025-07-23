#ifndef WATERTILE_H
#define WATERTILE_H

#include "Headers.h"

class WaterTile {
public:
	// tile scale, the 1:1 scale of the tile is 2x2
	static constexpr GLfloat TILE_SCALE = 60;
	static constexpr GLfloat TILE_SIZE = TILE_SCALE * 2;

	WaterTile(GLfloat centerX, GLfloat centerZ, GLfloat height);
	GLfloat getHeight();
	GLfloat getX();
	GLfloat getZ();
private:
	GLfloat height;
	GLfloat x, z;
};

#endif
