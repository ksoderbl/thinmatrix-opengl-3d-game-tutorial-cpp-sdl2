// package/namespace entities

#ifndef LIGHT_H
#define LIGHT_H

#include "Headers.h"

class Light {
public:
	Light(glm::vec3 position, glm::vec3 color) {
		this->position = position;
		this->color = color;
		glm::vec3 attenuation(1.0f, 0, 0);
		// no attenuation
		this->attenuation = attenuation;
	}
	Light(glm::vec3 position, glm::vec3 color, glm::vec3 attenuation) {
		this->position = position;
		this->color = color;
		this->attenuation = attenuation;
	}

	glm::vec3& getAttenuation() {
		return attenuation;
	}
	void setAttenuation(glm::vec3 attenuation) {
		this->attenuation = attenuation;
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
	glm::vec3 attenuation;
};

#endif
