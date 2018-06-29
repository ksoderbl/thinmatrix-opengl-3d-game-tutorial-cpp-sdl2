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
		TerrainTexturePack &texturePack, TerrainTexture& blendMap, string heightMap);
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

private:
	static constexpr GLfloat SIZE = 800;
	static constexpr GLfloat MAX_HEIGHT = 100;
	static constexpr GLfloat MAX_PIXEL_COLOR = 256 * 256 * 256;

	glm::vec3 position;
	RawModel* model;
	TerrainTexturePack& texturePack;
	TerrainTexture& blendMap;

	GLfloat getHeight(
		int x, int z,
		//BufferedImage& image,
		GLint tx_w,       /* width in pixels */
		GLint tx_h,       /* height in pixels */
		GLubyte *tx_data);
	glm::vec3 calculateNormal(
		int x, int z,
		//BufferedImage& image,
		GLint tx_w,       /* width in pixels */
		GLint tx_h,       /* height in pixels */
		GLubyte *tx_data);
};

#endif
