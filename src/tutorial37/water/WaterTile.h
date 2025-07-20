#ifndef WATERTILE_H
#define WATERTILE_H

#include "../Headers.h"

class WaterTile {
public:
	// tile scale, the 1:1 scale of the tile is 2x2
	static constexpr GLfloat DEFAULT_TILE_SCALE = 4*120;
	static constexpr GLfloat DEFAULT_TILE_SIZE = DEFAULT_TILE_SCALE * 2;

	WaterTile(GLfloat centerX, GLfloat centerZ, GLfloat height, GLfloat scale);
	GLfloat getHeight();
	GLfloat getX();
	GLfloat getZ();
	GLfloat getScale();
private:
	GLfloat height;
	GLfloat x, z;
	GLfloat scale;
};

#endif
