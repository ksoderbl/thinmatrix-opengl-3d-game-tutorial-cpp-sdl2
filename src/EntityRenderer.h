#ifndef RENDERER_H
#define RENDERER_H

#include "Headers.h"
#include "TexturedModel.h"
#include "Entity.h"
#include "StaticShader.h"

class EntityRenderer {
public:
	EntityRenderer(StaticShader& shader);
	void prepare();
	void render(std::map<TexturedModel*, vector<Entity*>*>* entities);
	void prepareTexturedModel(TexturedModel &model);
	void unbindTexturedModel();
	void prepareInstance(Entity &entity);
	//void render(Entity& entity, StaticShader& shader);
private:
	void createProjectionMatrix();
	
	glm::mat4 projectionMatrix;
	static constexpr GLfloat FOV = 70;
	static constexpr GLfloat NEAR_PLANE = 0.1f;
	static constexpr GLfloat FAR_PLANE = 10000;
	
	StaticShader& shader;
};

#endif
