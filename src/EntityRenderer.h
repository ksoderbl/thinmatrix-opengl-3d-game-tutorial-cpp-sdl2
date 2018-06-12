#ifndef RENDERER_H
#define RENDERER_H

#include "Headers.h"
#include "TexturedModel.h"
#include "Entity.h"
#include "StaticShader.h"

class EntityRenderer {
public:
	EntityRenderer(StaticShader& shader, glm::mat4& projectionMatrix);
	void render(std::map<TexturedModel*, vector<Entity*>*>* entities);
	void prepareTexturedModel(TexturedModel &model);
	void unbindTexturedModel();
	void prepareInstance(Entity &entity);
	//void render(Entity& entity, StaticShader& shader);
private:
	StaticShader& shader;
};

#endif
