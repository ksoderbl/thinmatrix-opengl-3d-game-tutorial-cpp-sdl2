#include "Terrain.h"

Terrain::Terrain(int gridX, int gridZ, Loader &loader,
	TerrainTexturePack &texturePack, TerrainTexture& blendMap)
	: texturePack(texturePack), blendMap(blendMap)
{
	this->position[0] = gridX * SIZE;
	this->position[1] = 0;
	this->position[2] = gridZ * SIZE;
	this->model = generateTerrain(loader);
}

RawModel* Terrain::generateTerrain(Loader &loader)
{
	vector<GLfloat> verticesArray;
	vector<GLfloat> normalsArray;
	vector<GLfloat> textureArray;
	vector<GLuint> indicesArray;

	for (int i = 0; i < VERTEX_COUNT; i++) {
		for (int j = 0; j < VERTEX_COUNT; j++) {
			GLfloat s = ((GLfloat)j) / ((GLfloat)(VERTEX_COUNT - 1));
			GLfloat t = ((GLfloat)i) / ((GLfloat)(VERTEX_COUNT - 1));
			verticesArray.push_back(s * SIZE);
			verticesArray.push_back(0);
			verticesArray.push_back(t * SIZE);
			normalsArray.push_back(0);
			normalsArray.push_back(1);
			normalsArray.push_back(0);
			textureArray.push_back(s);
			textureArray.push_back(t);
		}
	}
	
	for (int gz = 0; gz < VERTEX_COUNT - 1; gz++) {
		for (int gx = 0; gx < VERTEX_COUNT - 1; gx++) {
			GLuint topLeft = (gz * VERTEX_COUNT) + gx;
			GLuint topRight = topLeft + 1;
			GLuint bottomLeft = ((gz + 1) * VERTEX_COUNT) + gx;
			GLuint bottomRight = bottomLeft + 1;
			indicesArray.push_back(topLeft);
			indicesArray.push_back(bottomLeft);
			indicesArray.push_back(topRight);
			indicesArray.push_back(topRight);
			indicesArray.push_back(bottomLeft);
			indicesArray.push_back(bottomRight);
		}
	}
	
	return loader.loadToVAO(verticesArray, textureArray, normalsArray, indicesArray);
}
