// package entities

#ifndef ENTITY_H
#define ENTITY_H

#include "Headers.h"
#include "TexturedModel.h"

class Entity {
public:
	Entity(	TexturedModel &model,
		glm::vec3 position,
		GLfloat rotX, GLfloat rotY, GLfloat rotZ,
		GLfloat scale);

	Entity(	TexturedModel &model,
		glm::vec3 position,
		int textureIndex,
		GLfloat rotX, GLfloat rotY, GLfloat rotZ,
		GLfloat scale);

	GLfloat getTextureXOffset();
	GLfloat getTextureYOffset();

	void increasePosition(GLfloat dx, GLfloat dy, GLfloat dz);
	void increaseRotation(GLfloat dx, GLfloat dy, GLfloat dz);

	TexturedModel& getModel() { return model; }
	glm::vec3& getPosition() { return position; }
	GLfloat getRotX() { return rotX; }
	GLfloat getRotY() { return rotY; }
	GLfloat getRotZ() { return rotZ; }
	GLfloat getScale() { return scale; }
private:
	TexturedModel& model;
	glm::vec3 position;
	GLfloat rotX, rotY, rotZ;
	GLfloat scale;
	int textureIndex = 0;
};

#endif
