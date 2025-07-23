#ifndef RAWMODEL_H
#define RAWMODEL_H

#include "../Headers.h"

class RawModel {
private:
	GLuint vaoID;
	int vertexCount;
public:
	RawModel(GLuint vaoID, int vertexCount);
	GLuint getVaoID() { return vaoID; }
	int getVertexCount() { return vertexCount; }
};

#endif
