#ifndef LOADER_H
#define LOADER_H

#include "Headers.h"

#include "RawModel.h"

#include <vector>

using std::vector;

class Loader {
public:
	Loader();
	~Loader();
	RawModel* loadToVAO(vector<GLfloat>&positions, vector<GLuint>&indices);
	void cleanUp();
private:
	GLuint createVAO();
	void storeDataInAttributeList(int attributeNumber, vector<GLfloat>&data);
	void unbindVAO(GLuint vaoID);
	GLuint bindIndicesBuffer(vector<GLuint>&indices);
	
	vector<GLuint> *vaos;
	vector<GLuint> *vbos;
};

#endif
