// package terrains

#ifndef TERRAIN_H
#define TERRAIN_H

#include "../Headers.h"
#include "../models/RawModel.h"
#include "../renderEngine/Loader.h"
#include "TerrainTexturePack.h"
#include "TerrainTexture.h"
#include "../textures/TextureData.h"
#include "HeightsGenerator.h"

class Terrain {
public:
	Terrain(int gridX, int gridZ, Loader &loader,
		TerrainTexturePack &texturePack, TerrainTexture& blendMap, string heightMap);
	GLfloat getHeightOfTerrain(GLfloat worldX, GLfloat worldZ);
	RawModel* generateTerrain(Loader &loader, string heightMap);
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

	static constexpr GLfloat SIZE = 4*300;
	static constexpr GLfloat MAX_HEIGHT = 2*40;
	static constexpr GLfloat MAX_PIXEL_COLOR = 256 * 256 * 256;

private:
	glm::vec3 position;
	RawModel* model;
	TerrainTexturePack& texturePack;
	TerrainTexture& blendMap;
	GLfloat **heights;
	int heightsLength;

	GLfloat getHeight(int x, int z, int stepSize, HeightsGenerator& generator);
	glm::vec3 calculateNormal(int x, int z, int stepSize, HeightsGenerator& generator);

};

#endif
