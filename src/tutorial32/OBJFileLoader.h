#ifndef OBJFILELOADER_H
#define OBJFILELOADER_H

#include "Headers.h"
#include "Loader.h"
#include "Vertex.h"
#include "ModelData.h"

class OBJFileLoader {
public:
	static RawModel *loadOBJ(string objFileName, Loader& loader);
private:
	static void processVertex(
		int index,
		int textureIndex,
		int normalIndex,
		vector<Vertex*>& vertices,
		vector<GLuint>& indices);

	static GLfloat convertDataToArrays(
		vector<Vertex*>& vertices,
		vector<glm::vec2>& textures,
		vector<glm::vec3>& normals,
		vector<GLfloat>& verticesArray,
		vector<GLfloat>& texturesArray,
		vector<GLfloat>& normalsArray);

	static void dealWithAlreadyProcessedVertex(
		Vertex *previousVertex,
		int newTextureIndex,
		int newNormalIndex,
		vector<GLuint>& indices,
		vector<Vertex*>& vertices);

	static void removeUnusedVertices(vector<Vertex*>& vertices);
};

#endif
