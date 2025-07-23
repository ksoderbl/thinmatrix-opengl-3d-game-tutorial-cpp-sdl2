// package terrains

#ifndef TERRAIN_H
#define TERRAIN_H

#include "Headers.h"
#include "RawModel.h"
#include "ModelTexture.h"
#include "Loader.h"

class Terrain {
public:
	Terrain(int gridX, int gridZ, Loader &loader, ModelTexture &texture);
	RawModel* generateTerrain(Loader &loader);
	glm::vec3& getPosition() { 
		return position;
	}
	RawModel& getModel() {
		return *model;
	}
	ModelTexture& getTexture() {
		return texture;
	}
	

private:
	static constexpr GLfloat SIZE = 800;
	static constexpr int VERTEX_COUNT = 128;
	glm::vec3 position;
	RawModel* model;
	ModelTexture& texture;
};

#endif
