#ifndef RAWMODEL_H
#define RAWMODEL_H

#include "Headers.h"

class RawModel {
private:
	GLuint vaoID;
	GLuint iboID;
	GLuint shaderProgram;
	int vertexCount;
public:
	RawModel(GLuint vaoID, GLuint shaderProgram, GLuint iboID, int vertexCount);
	GLuint getVaoID() { return vaoID; }
	GLuint getIboID() { return iboID; }
	GLuint getShaderProgram() { return shaderProgram; }
	int getVertexCount() { return vertexCount; }
};

#endif
