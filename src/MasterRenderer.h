// package/namespace renderEngine

#ifndef MASTERRENDERER_H
#define MASTERRENDERER_H

#include "Headers.h"
#include "StaticShader.h"
#include "EntityRenderer.h"
#include "TexturedModel.h"
#include "Entity.h"
#include "Light.h"
#include "Camera.h"
#include "Terrain.h"
#include "TerrainShader.h"
#include "TerrainRenderer.h"

class MasterRenderer {
public:
	MasterRenderer();
	~MasterRenderer();
	static void enableCulling();
	static void disableCulling();
	void prepare();
	void render(Light& sun, Camera& camera);
	void processTerrain(Terrain& terrain);
	void processEntity(Entity& entity);
	void cleanUp();

private:
	void createProjectionMatrix();

	glm::mat4 projectionMatrix;
	static constexpr GLfloat FOV = 70;
	static constexpr GLfloat NEAR_PLANE = 0.1f;
	static constexpr GLfloat FAR_PLANE = 10000;
	static constexpr GLfloat SKY_RED = 0.5f;
	static constexpr GLfloat SKY_GREEN = 0.5f;
	static constexpr GLfloat SKY_BLUE = 0.5f;

	StaticShader* shader;
	EntityRenderer* renderer;
	std::map<TexturedModel*, vector<Entity*>*>* entities;

	TerrainShader* terrainShader;
	TerrainRenderer* terrainRenderer;
	vector<Terrain*>* terrains;
};

#endif
