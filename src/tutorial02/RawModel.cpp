
#include "RawModel.h"

RawModel::RawModel(GLuint vaoID, GLuint shaderProgram, int vertexCount)
{
	this->vaoID = vaoID;
	this->shaderProgram = shaderProgram;
	this->vertexCount = vertexCount;
}
