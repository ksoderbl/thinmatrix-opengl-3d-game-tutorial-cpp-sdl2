// package/namespace textures

#ifndef MODELTEXTURE_H
#define MODELTEXTURE_H

#include "../Headers.h"

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

	bool getHasTransparency() {
		return hasTransparency;
	}

	void setHasTransparency(bool hasTransparency) {
		this->hasTransparency = hasTransparency;
	}

	bool getUseFakeLighting() {
		return useFakeLighting;
	}

	void setUseFakeLighting(bool useFakeLighting) {
		this->useFakeLighting = useFakeLighting;
	}

	int getNumberOfRows() {
		return numberOfRows;
	}

	void setNumberOfRows(int numberOfRows) {
		this->numberOfRows = numberOfRows;
	}

	GLuint getNormalMap() {
		return normalMap;
	}

	void setNormalMap(GLuint normalMap) {
		this->normalMap = normalMap;
	}

private:
	GLuint textureID;
	GLuint normalMap;
	GLfloat shineDamper = 1;
	GLfloat reflectivity = 0;
	bool hasTransparency = false;
	bool useFakeLighting = false;

	// OpenGL 3D Game Tutorial 23: Texture Atlases
	int numberOfRows = 1;
};

#endif
