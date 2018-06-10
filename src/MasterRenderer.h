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
	MasterRenderer() {
		shader = new StaticShader();
		renderer = new EntityRenderer(*shader);
		entities = new std::map<TexturedModel*, vector<Entity*>*>;
	}
	
	~MasterRenderer() {
		delete shader;
	}

	void render(Light& sun, Camera& camera);

	void processEntity(Entity &entity);
	
	void cleanUp() {
		shader->cleanUp();
	}

private:
	StaticShader* shader;
	EntityRenderer* renderer;
	std::map<TexturedModel*, vector<Entity*>*>* entities;
};

#endif
