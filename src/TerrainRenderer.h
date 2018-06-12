#ifndef TERRAINRENDERER_H
#define TERRAINRENDERER_H

#include "Headers.h"
#include "TexturedModel.h"
#include "Entity.h"
#include "TerrainShader.h"

class TerrainRenderer {
public:
	TerrainRenderer(TerrainShader& shader, glm::mat4& projectionMatrix);
	void render(std::map<TexturedModel*, vector<Entity*>*>* entities);
	void prepareTexturedModel(TexturedModel &model);
	void unbindTexturedModel();
	void prepareInstance(Entity &entity);
	//void render(Entity& entity, StaticShader& shader);
private:
	TerrainShader& shader;
};

#endif
