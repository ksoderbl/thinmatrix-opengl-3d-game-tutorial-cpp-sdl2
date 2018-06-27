// package terrains

#ifndef TERRAIN_H
#define TERRAIN_H

#include "Headers.h"
#include "RawModel.h"
#include "Loader.h"
#include "TerrainTexturePack.h"
#include "TerrainTexture.h"

class Terrain {
public:
	Terrain(int gridX, int gridZ, Loader &loader,
		TerrainTexturePack &texturePack, TerrainTexture& blendMap);
	RawModel* generateTerrain(Loader &loader);
	glm::vec3& getPosition() { 
		return position;
	}
	RawModel& getModel() {
		return *model;
	}
	TerrainTexturePack& getTexturePack() {
		return texturePack;
	}
	TerrainTexture& getBlendMap() {
		return blendMap;
	}
	

private:
	static constexpr GLfloat SIZE = 800;
	static constexpr int VERTEX_COUNT = 128;
	glm::vec3 position;
	RawModel* model;
	TerrainTexturePack& texturePack;
	TerrainTexture& blendMap;
};

#endif
