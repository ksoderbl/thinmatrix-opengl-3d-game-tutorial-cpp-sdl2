#include "TextMeshData.h"

TextMeshData::TextMeshData(
	vector<GLfloat> vertexPositions,
	vector<GLfloat> textureCoords)
{
	this->vertexPositions = vertexPositions;
	this->textureCoords = textureCoords;
}

vector<GLfloat>& TextMeshData::getVertexPositions()
{
	return vertexPositions;
}

vector<GLfloat>& TextMeshData::getTextureCoords()
{
	return textureCoords;
}

int TextMeshData::getVertexCount()
{
	return vertexPositions.size() / 2;
}
