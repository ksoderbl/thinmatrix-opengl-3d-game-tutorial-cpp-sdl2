#include "VertexNM.h"

VertexNM::VertexNM(int index, glm::vec3 position)
{
	this->index = index;
	this->position = position;
	this->length = glm::length(position);
}

int VertexNM::getIndex()
{
	return index;
}

GLfloat VertexNM::getLength()
{
	return length;
}
     
bool VertexNM::isSet()
{
    return textureIndex != NO_INDEX && normalIndex != NO_INDEX;
}
     
bool VertexNM::hasSameTextureAndNormal(int textureIndexOther, int normalIndexOther)
{
	return textureIndexOther == textureIndex && normalIndexOther == normalIndex;
}
     
void VertexNM::setTextureIndex(int textureIndex)
{
	this->textureIndex = textureIndex;
}
     
void VertexNM::setNormalIndex(int normalIndex)
{
	this->normalIndex = normalIndex;
}
 
glm::vec3& VertexNM::getPosition()
{
	return position;
}
 
int VertexNM::getTextureIndex()
{
	return textureIndex;
}
 
int VertexNM::getNormalIndex()
{
	return normalIndex;
}
 
VertexNM* VertexNM::getDuplicateVertex()
{
	return duplicateVertex;
}
 
void VertexNM::setDuplicateVertex(VertexNM* duplicateVertex)
{
	this->duplicateVertex = duplicateVertex;
}
 
