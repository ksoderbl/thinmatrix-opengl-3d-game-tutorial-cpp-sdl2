#ifndef TERRAINTEXTURE_H
#define TERRAINTEXTURE_H

#include "../Headers.h"

class TerrainTexture {
public:
	TerrainTexture(GLuint textureID);
	GLuint getTextureId();
private:
	GLuint textureID;
};

#endif
