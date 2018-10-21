#ifndef TEXTUREDATA_H
#define TEXTUREDATA_H

#include "../Headers.h"

class TextureData {
public:
	TextureData(GLubyte* buffer, GLsizei width, GLsizei height);
	GLsizei getWidth();
	GLsizei getHeight();
	GLubyte* getBuffer();
private:
	GLsizei width;
	GLsizei height;
	GLubyte* buffer;
};

#endif
