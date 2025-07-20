#ifndef MODELDATA_H
#define MODELDATA_H

#include "../Headers.h"

class ModelData
{
public:
	ModelData(
		vector<GLfloat>& vertices,
		vector<GLfloat>& textureCoords,
		vector<GLfloat>& normals,
		vector<GLuint>& indices,
		GLfloat furthestPoint);
	// TODO: destructor

	vector<GLfloat>& getVertices();
	vector<GLfloat>& getTextureCoords();
	vector<GLfloat>& getNormals();
	vector<GLuint>& getIndices();
	GLfloat getFurthestPoint();
private:
	vector<GLfloat> vertices;
	vector<GLfloat> textureCoords;
	vector<GLfloat> normals;
	vector<GLuint> indices;
	GLfloat furthestPoint;
};

#endif
