#ifndef RENDERER_H
#define RENDERER_H

#include "TexturedModel.h"
#include "Entity.h"
#include "StaticShader.h"

class Renderer {
public:
	Renderer(StaticShader& shader);
	void prepare();
	void render(Entity& entity, StaticShader& shader);
private:
	void createProjectionMatrix();
	
	glm::mat4 projectionMatrix;
	static constexpr GLfloat FOV = 70;
	static constexpr GLfloat NEAR_PLANE = 0.1f;
	static constexpr GLfloat FAR_PLANE = 1000;
	
};

#endif