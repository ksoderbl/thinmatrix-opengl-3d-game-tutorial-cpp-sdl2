#ifndef PARTICLETEXTURE_H
#define PARTICLETEXTURE_H

#include "../Headers.h"

class ParticleTexture {
public:
	ParticleTexture(GLuint textureID, int numberOfRows);
        GLuint getTextureId();
	int getNumberOfRows();
private:
        GLuint textureID;
	int numberOfRows = 1;
};

#endif
