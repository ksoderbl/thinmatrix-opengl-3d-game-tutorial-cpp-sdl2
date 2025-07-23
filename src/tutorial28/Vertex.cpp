#include "Vertex.h"

Vertex::Vertex(int index, glm::vec3 position)
{
	this->index = index;
    this->position = position;
    this->length = glm::length(position);
}

int Vertex::getIndex()
{
	return index;
}

GLfloat Vertex::getLength()
{
	return length;
}
     
bool Vertex::isSet()
{
    return textureIndex != NO_INDEX && normalIndex != NO_INDEX;
}
     
bool Vertex::hasSameTextureAndNormal(int textureIndexOther, int normalIndexOther)
{
	return textureIndexOther == textureIndex && normalIndexOther == normalIndex;
}
     
void Vertex::setTextureIndex(int textureIndex)
{
	this->textureIndex = textureIndex;
}
     
void Vertex::setNormalIndex(int normalIndex)
{
	this->normalIndex = normalIndex;
}
 
glm::vec3& Vertex::getPosition()
{
	return position;
}
 
int Vertex::getTextureIndex()
{
	return textureIndex;
}
 
int Vertex::getNormalIndex()
{
	return normalIndex;
}
 
Vertex* Vertex::getDuplicateVertex()
{
	return duplicateVertex;
}
 
void Vertex::setDuplicateVertex(Vertex* duplicateVertex)
{
	this->duplicateVertex = duplicateVertex;
}
 
