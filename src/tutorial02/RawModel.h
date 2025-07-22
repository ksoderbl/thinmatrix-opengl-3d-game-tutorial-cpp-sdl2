#ifndef RAWMODEL_H
#define RAWMODEL_H

#include "Headers.h"

class RawModel {
private:
	GLuint vaoID;
	GLuint shaderProgram;
	int vertexCount;
public:
	RawModel(GLuint vaoID, GLuint shaderProgram, int vertexCount);
	GLuint getVaoID() { return vaoID; }
	GLuint getShaderProgram() { return shaderProgram; }
	int getVertexCount() { return vertexCount; }
};

#endif
