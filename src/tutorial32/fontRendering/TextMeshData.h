#ifndef TEXTMESHDATA_H
#define TEXTMESHDATA_H

#include "../Headers.h"

/**
 * Stores the vertex data for all the quads on which a text will be rendered.
 */
class TextMeshData {
public:
	TextMeshData(vector<GLfloat> vertexPositions,
		     vector<GLfloat> textureCoords);

	vector<GLfloat>& getVertexPositions();
	vector<GLfloat>& getTextureCoords();

	int getVertexCount();
	
private:
	vector<GLfloat> vertexPositions;
	vector<GLfloat> textureCoords;
};

#endif
