// package/namespace renderEngine

#ifndef MASTERRENDERER_H
#define MASTERRENDERER_H

#include "Headers.h"
#include "StaticShader.h"
#include "Renderer.h"
#include "TexturedModel.h"
#include "Entity.h"
#include "Light.h"
#include "Camera.h"

class MasterRenderer {
public:
	MasterRenderer() {
		shader = new StaticShader();
		renderer = new Renderer(*shader);
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
	




/*
	Light(glm::vec3 position, glm::vec3 color) {
		this->position = position;
		this->color = color;
	}
	glm::vec3& getPosition() {
		return position;
	}
	void setPosition(glm::vec3 position) {
		this->position = position;
	}
	glm::vec3& getColor() {
		return color;
	}
	void setColor(glm::vec3 color) {
		this->color = color;
	}
	*/
private:
	StaticShader* shader;
	Renderer* renderer;
	std::map<TexturedModel*, vector<Entity*>*>* entities;
};

#endif
