#ifndef OBJFILELOADER_H
#define OBJFILELOADER_H

#include "Headers.h"
#include "Loader.h"
#include "Vertex.h"
#include "ModelData.h"

class OBJFileLoader {
public:
	ModelData *loadOBJ(string objFileName);
private:
	void processVertex(
		int index,
		int textureIndex,
		int normalIndex,
		vector<Vertex*>& vertices,
		vector<GLuint>& indices);

	GLfloat convertDataToArrays(
		vector<Vertex*>& vertices,
		vector<glm::vec2>& textures,
		vector<glm::vec3>& normals,
		vector<GLfloat>& verticesArray,
		vector<GLfloat>& texturesArray,
		vector<GLfloat>& normalsArray);

	void removeUnusedVertices(vector<Vertex*>& vertices);
};

#endif
