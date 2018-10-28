// package terrains

#ifndef HEIGHTSGENERATOR_H
#define HEIGHTSGENERATOR_H

#include "../Headers.h"
#include "../models/RawModel.h"
#include "../renderEngine/Loader.h"
#include "TerrainTexturePack.h"
#include "TerrainTexture.h"
#include "../textures/TextureData.h"

class HeightsGenerator {
public:
	HeightsGenerator(Loader &loader, string heightMap, int stepSize);
	GLfloat generateHeight(int x, int z);
	int getVertexCount() { return vertexCount; }
	
	//static constexpr GLfloat AMPLITUDE = 70;
	static constexpr GLfloat MAX_HEIGHT = 80;
private:
	GLfloat getInterpolatedNoise(GLfloat x, GLfloat z);
	GLfloat interpolate(GLfloat a, GLfloat b, GLfloat blend);
	GLfloat getSmoothNoise(int x, int z);
	GLfloat getNoise(int x, int z);

	TextureData *image;
	int stepSize;
	int vertexCount;

	int seed;
	GLfloat amplitude;
	int octaves;
	double roughness;


};

#endif
