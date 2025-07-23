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
#include "SkyboxRenderer.h"
#include "Loader.h"
#include "DisplayManager.h"

class MasterRenderer {
public:
	MasterRenderer(Loader& loader, DisplayManager& display);
	~MasterRenderer();
	static void enableCulling();
	static void disableCulling();
	void prepare();
	void renderScene(
		vector<Entity*>& entities,
		vector<Terrain*>& terrains,
		vector<Light*>&lights,
		Camera& camera,
		glm::vec4& clipPlane,
		bool useClipping,
		//Player& player,
		DisplayManager& display);
	void render(
		vector<Light*>& lights,
		Camera& camera,
		glm::vec4& clipPlane,
		bool useClipping,
		DisplayManager& display);
	void processTerrain(Terrain& terrain);
	void processEntity(Entity& entity);
	void cleanUp();
	glm::mat4& getProjectionMatrix();
	GLfloat getNearPlane() { return NEAR_PLANE; }
	GLfloat getFarPlane() { return FAR_PLANE; }

	static constexpr GLfloat FOV = 70;
	static constexpr GLfloat NEAR_PLANE = 0.1f;
	static constexpr GLfloat FAR_PLANE = 10000.0f;
	static constexpr GLfloat SKY_RED = 0.5444f;
	static constexpr GLfloat SKY_GREEN = 0.62f;
	static constexpr GLfloat SKY_BLUE = 0.69f;

private:
	void createProjectionMatrix(DisplayManager& display);

	glm::mat4 projectionMatrix;

	StaticShader* shader;
	EntityRenderer* renderer;
	std::map<TexturedModel*, vector<Entity*>*>* entitiesMap;

	TerrainShader* terrainShader;
	TerrainRenderer* terrainRenderer;
	vector<Terrain*>* terrains;

	SkyboxRenderer* skyboxRenderer;
};

#endif
