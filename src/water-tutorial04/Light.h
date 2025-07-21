// package/namespace entities

#ifndef LIGHT_H
#define LIGHT_H

#include "Headers.h"

class Light {
public:
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
private:
	glm::vec3 position;
	glm::vec3 color;
};

#endif
