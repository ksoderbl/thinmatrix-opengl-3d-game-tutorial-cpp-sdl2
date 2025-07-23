#ifndef TERRAINRENDERER_H
#define TERRAINRENDERER_H

#include "../Headers.h"
#include "../models/TexturedModel.h"
#include "../entities/Entity.h"
#include "TerrainShader.h"
#include "Terrain.h"

class TerrainRenderer {
public:
	TerrainRenderer(TerrainShader& shader, glm::mat4& projectionMatrix);
	void render(vector<Terrain*>* terrains);
	void prepareTerrain(Terrain& terrain);
	void bindTextures(Terrain& terrain);
	void loadModelMatrix(Terrain& terrain);
	void unbindTexturedModel();
private:
	TerrainShader& shader;
};

#endif
