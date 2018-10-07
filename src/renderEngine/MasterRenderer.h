// package/namespace renderEngine

#ifndef MASTERRENDERER_H
#define MASTERRENDERER_H

#include "../Headers.h"
#include "../StaticShader.h"
#include "EntityRenderer.h"
#include "../normalMappingRenderer/NormalMappingRenderer.h"
#include "../models/TexturedModel.h"
#include "../Entity.h"
#include "../Light.h"
#include "../Camera.h"
#include "../Terrain.h"
#include "../TerrainShader.h"
#include "TerrainRenderer.h"
#include "../skybox/SkyboxRenderer.h"
#include "Loader.h"
#include "DisplayManager.h"

class MasterRenderer {
public:
	GLfloat FOV;
	GLfloat NEAR_PLANE;
	GLfloat FAR_PLANE;
	GLfloat RED;
	GLfloat GREEN;
	GLfloat BLUE;
	GLfloat FOG_DENSITY;
	GLfloat FOG_GRADIENT;

	MasterRenderer();
	~MasterRenderer();
	void init(Loader& loader);

	void enableCulling();
	void disableCulling();

	void prepare();
	void renderScene(
		vector<Entity*>& entities,
		vector<Entity*>& normalMapEntities,
		vector<Terrain*>& terrains,
		vector<Light*>&lights,
		Camera& camera,
		glm::vec4& clipPlane,
		bool useClipping);
	void render(
		vector<Light*>& lights,
		Camera& camera,
		glm::vec4& clipPlane,
		bool useClipping);
	void processTerrain(Terrain& terrain);
	void processEntity(Entity& entity);
	void processNormalMapEntity(Entity& entity);
	void cleanUp();
	glm::mat4& getProjectionMatrix();
	GLfloat getNearPlane() { return NEAR_PLANE; }
	GLfloat getFarPlane() { return FAR_PLANE; }

private:
	void createProjectionMatrix();

	glm::mat4 projectionMatrix;

	StaticShader* shader;
	EntityRenderer* renderer;

	TerrainShader* terrainShader;
	TerrainRenderer* terrainRenderer;

	NormalMappingRenderer* normalMapRenderer;

	SkyboxRenderer* skyboxRenderer;

	std::map<TexturedModel*, vector<Entity*>*>* entitiesMap;
	std::map<TexturedModel*, vector<Entity*>*>* normalMapEntitiesMap;
	vector<Terrain*>* terrains;
};

extern MasterRenderer masterRenderer;

#endif
