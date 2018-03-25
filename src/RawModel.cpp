
#include "RawModel.h"

RawModel::RawModel(GLuint vaoID, GLuint shaderProgram, GLuint iboID, int vertexCount)
{
	this->vaoID = vaoID;
	this->shaderProgram = shaderProgram;
	this->iboID = iboID;
	this->vertexCount = vertexCount;
}
