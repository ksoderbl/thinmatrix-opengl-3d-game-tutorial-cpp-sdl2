// package/namespace textures

#ifndef MODELTEXTURE_H
#define MODELTEXTURE_H

#include "Headers.h"

class ModelTexture {
public:
	ModelTexture(GLuint id);
	GLuint getID() {
		return textureID;
	}

	GLfloat getShineDamper() {
		return shineDamper;
	}

	void setShineDamper(GLfloat shineDamper) {
		this->shineDamper = shineDamper;
	}

	GLfloat getReflectivity() {
		return reflectivity;
	}

	void setReflectivity(GLfloat reflectivity) {
		this->reflectivity = reflectivity;
	}


private:
	GLuint textureID;
	GLfloat shineDamper = 1;
	GLfloat reflectivity = 0;
};

#endif
