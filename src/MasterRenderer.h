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

class MasterRenderer {
public:
	MasterRenderer();
	~MasterRenderer();
	void prepare(void);
	void render(Light& sun, Camera& camera);
	void processEntity(Entity &entity);
	void cleanUp(void);

private:
	void createProjectionMatrix(void);

	glm::mat4 projectionMatrix;
	static constexpr GLfloat FOV = 70;
	static constexpr GLfloat NEAR_PLANE = 0.1f;
	static constexpr GLfloat FAR_PLANE = 10000;

	StaticShader* shader;
	EntityRenderer* renderer;
	std::map<TexturedModel*, vector<Entity*>*>* entities;

};

#endif
