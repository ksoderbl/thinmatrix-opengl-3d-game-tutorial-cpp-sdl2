#ifndef NORMALMAPPINGRENDERER_H
#define NORMALMAPPINGRENDERER_H

#include "Headers.h"
#include "TexturedModel.h"
#include "Entity.h"
#include "StaticShader.h"

class NormalMappingRenderer {
public:
	NormalMappingRenderer(StaticShader& shader, glm::mat4& projectionMatrix);
	void render(std::map<TexturedModel*, vector<Entity*>*>* entities);
	void prepareTexturedModel(TexturedModel &model);
	void unbindTexturedModel();
	void prepareInstance(Entity &entity);
private:
	StaticShader& shader;
};

#endif
