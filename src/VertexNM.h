#ifndef VERTEXNM_H
#define VERTEXNM_H

#include "Headers.h"

class VertexNM {
public:
	VertexNM(int index, glm::vec3 position);
	int getIndex();
	GLfloat getLength();
	bool isSet();
	bool hasSameTextureAndNormal(int textureIndexOther, int normalIndexOther);
	void setTextureIndex(int textureIndex);
	void setNormalIndex(int normalIndex);
	glm::vec3& getPosition();
	int getTextureIndex();
	int getNormalIndex();
	VertexNM* getDuplicateVertex();
	void setDuplicateVertex(VertexNM* duplicateVertex);

private:
	static constexpr int NO_INDEX = -1;
	glm::vec3 position;
	int textureIndex = NO_INDEX;
	int normalIndex = NO_INDEX;
	VertexNM *duplicateVertex = nullptr;
	int index;
	GLfloat length;
};


#endif
