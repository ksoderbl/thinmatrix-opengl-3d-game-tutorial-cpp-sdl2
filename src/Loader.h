#ifndef LOADER_H
#define LOADER_H

#include "Headers.h"
#include "RawModel.h"

class Loader {
public:
	Loader();
	~Loader();
	RawModel* loadToVAO(
		vector<GLfloat>&positions,
		vector<GLfloat>&textureCoords,
		vector<GLuint>&indices);
	void cleanUp();
private:
	GLuint createVAO();
	void storeDataInAttributeList(int attributeNumber, int coordinateSize, vector<GLfloat>&data);
	void unbindVAO(GLuint vaoID);
	GLuint bindIndicesBuffer(vector<GLuint>&indices);
	
	vector<GLuint> *vaos;
	vector<GLuint> *vbos;
	vector<GLuint> *textures;
};

#endif
