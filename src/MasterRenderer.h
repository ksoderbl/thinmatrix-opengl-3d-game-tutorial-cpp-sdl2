// package/namespace renderEngine

#ifndef MASTERRENDERER_H
#define MASTERRENDERER_H

#include "Headers.h"
#include "StaticShader.h"
#include "EntityRenderer.h"
#include "NormalMappingRenderer.h"
#include "TexturedModel.h"
#include "Entity.h"
#include "Light.h"
#include "Camera.h"
#include "Terrain.h"
#include "TerrainShader.h"
#include "TerrainRenderer.h"
#include "SkyboxRenderer.h"
#include "Loader.h"
#include "DisplayManager.h"

class MasterRenderer {
public:
	MasterRenderer(Loader& loader);
	~MasterRenderer();
	static void enableCulling();
	static void disableCulling();
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

	static constexpr GLfloat FOV = 70;
	static constexpr GLfloat NEAR_PLANE = 0.1f;
	static constexpr GLfloat FAR_PLANE = 10000.0f;
	//static constexpr GLfloat RED = 0.5444f;
	//static constexpr GLfloat GREEN = 0.62f;
	//static constexpr GLfloat BLUE = 0.69f;
	//For Tutorial 30 Cel Shading
	static constexpr GLfloat RED = 0.9444f;
	static constexpr GLfloat GREEN = 0.52f;
	static constexpr GLfloat BLUE = 0.79f;

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

#endif
