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
	RawModel* loadToVAO(GLfloat positions[], int numPositions);
	void cleanUp();
private:
	GLuint createVAO();
	GLuint storeDataInAttributeList(int attributeNumber, GLfloat data[], int numData);
	void unbindVAO(GLuint vaoID);
	
	vector<GLuint> *vaos;
	vector<GLuint> *vbos;
};

#endif
