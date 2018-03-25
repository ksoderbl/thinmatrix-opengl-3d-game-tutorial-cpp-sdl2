
#include "RawModel.h"

RawModel::RawModel(GLuint vaoID, GLuint iboID, int vertexCount)
{
	this->vaoID = vaoID;
	this->iboID = iboID;
	this->vertexCount = vertexCount;
}
