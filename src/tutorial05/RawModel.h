#ifndef RAWMODEL_H
#define RAWMODEL_H

#include "Headers.h"

class RawModel {
private:
	GLuint vaoID;
	GLuint iboID;
	int vertexCount;
public:
	RawModel(GLuint vaoID, GLuint iboID, int vertexCount);
	GLuint getVaoID() { return vaoID; }
	GLuint getIboID() { return iboID; }
	int getVertexCount() { return vertexCount; }
};

#endif
