#ifndef NORMALMAPPEDOBJFILELOADER_H
#define NORMALMAPPEDOBJFILELOADER_H

#include "../Headers.h"
#include "../renderEngine/Loader.h"
#include "../Vertex.h"
#include "../ModelData.h"

class NormalMappingObjLoader {
public:
	static RawModel *loadOBJ(string objFileName, Loader& loader);
private:
	static Vertex* processVertex(
		int index,
		int textureIndex,
		int normalIndex,
		vector<Vertex*>& vertices,
		vector<GLuint>& indices);

	static void calculateTangents(
		Vertex* v0, Vertex* v1, Vertex* v2,
		vector<glm::vec2>& textures);

	static GLfloat convertDataToArrays(
		vector<Vertex*>& vertices,
		vector<glm::vec2>& textures,
		vector<glm::vec3>& normals,
		vector<GLfloat>& verticesArray,
		vector<GLfloat>& texturesArray,
		vector<GLfloat>& normalsArray,
		vector<GLfloat>& tangentsArray
		);

	static Vertex* dealWithAlreadyProcessedVertex(
		Vertex *previousVertex,
		int newTextureIndex,
		int newNormalIndex,
		vector<GLuint>& indices,
		vector<Vertex*>& vertices);

	static void removeUnusedVertices(vector<Vertex*>& vertices);
};

#endif
