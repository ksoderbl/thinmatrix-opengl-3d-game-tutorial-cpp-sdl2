// package/namespace textures

#ifndef MODELTEXTURE_H
#define MODELTEXTURE_H

#include "Headers.h"

class ModelTexture {
public:
	ModelTexture(GLuint id);
	GLuint getID() { return textureID; }
private:
	GLuint textureID;
};

#endif
