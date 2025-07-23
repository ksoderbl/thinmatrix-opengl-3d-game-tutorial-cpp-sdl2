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
	void renderScene(
		vector<Entity*>& entities,
		vector<Terrain*>& terrains,
		vector<Light*>&lights,
		Camera& camera,
		glm::vec4& clipPlane,
		Player& player,
		bool pausing,
		TexturedModel* stallTexturedModel);
	void render(vector<Light*>& lights, Camera& camera, glm::vec4& clipPlane);
	void processTerrain(Terrain& terrain);
	void processEntity(Entity& entity);
	void cleanUp();
	glm::mat4& getProjectionMatrix();

private:
	void createProjectionMatrix();

	glm::mat4 projectionMatrix;
	static constexpr GLfloat FOV = 70;
	static constexpr GLfloat NEAR_PLANE = 0.1f;
	static constexpr GLfloat FAR_PLANE = 10000;
	static constexpr GLfloat SKY_RED = 0.6f;
	static constexpr GLfloat SKY_GREEN = 0.8f;
	static constexpr GLfloat SKY_BLUE = 1.0f;

	StaticShader* shader;
	EntityRenderer* renderer;
	std::map<TexturedModel*, vector<Entity*>*>* entitiesMap;

	TerrainShader* terrainShader;
	TerrainRenderer* terrainRenderer;
	vector<Terrain*>* terrains;
};

#endif
