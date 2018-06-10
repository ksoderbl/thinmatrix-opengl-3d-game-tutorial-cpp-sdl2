// package terrains

#ifndef TERRAIN_H
#define TERRAIN_H

#include "Headers.h"
#include "RawModel.h"
#include "ModelTexture.h"
#include "Loader.h"

class Terrain {
public:
	Terrain(int gridX, int gridY, Loader &loader, ModelTexture &texture);
	RawModel* generateTerrain(Loader &loader);

private:
	static constexpr GLfloat SIZE = 800;
	static constexpr int VERTEX_COUNT = 128;
	GLfloat x, y;
	RawModel* model;
	ModelTexture& texture;
};

#endif
