#include "ModelData.h"

ModelData::ModelData(
		vector<GLfloat>& vertices,
		vector<GLfloat>& textureCoords,
		vector<GLfloat>& normals,
		vector<GLuint>& indices,
		GLfloat furthestPoint)
{
	for (int i = 0; i < (int) vertices.size(); i++) {
		this->vertices.push_back(vertices[i]);
	}
	for (int i = 0; i < (int) textureCoords.size(); i++) {
		this->textureCoords.push_back(textureCoords[i]);
	}
	for (int i = 0; i < (int) normals.size(); i++) {
		this->normals.push_back(normals[i]);
	}
	for (int i = 0; i < (int) indices.size(); i++) {
		this->indices.push_back(indices[i]);
	}
	this->furthestPoint = furthestPoint;
}

vector<GLfloat>& ModelData::getVertices()
{
	return vertices;
}
 
vector<GLfloat>& ModelData::getTextureCoords()
{
	return textureCoords;
}
 
vector<GLfloat>& ModelData::getNormals()
{
	return normals;
}
 
vector<GLuint>& ModelData::getIndices()
{
		return indices;
}
 
GLfloat ModelData::getFurthestPoint()
{
	return furthestPoint;
}
