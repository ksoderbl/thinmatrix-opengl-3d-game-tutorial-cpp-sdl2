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
		vector<GLfloat>&normals,
		vector<GLuint>&indices);
	GLuint loadTexture(string fileName);
	void cleanUp();
private:
	GLuint createVAO();
	GLuint createVBO(GLenum target);
	void storeDataInAttributeList(int attributeNumber, int coordinateSize, vector<GLfloat>&data);
	void unbindVAO();
	void bindIndicesBuffer(vector<GLuint>&indices);
	GLubyte* LoadPNGImage(string imageFile, GLint *width, GLint *height, GLenum *format);

	vector<GLuint> *vaos;
	vector<GLuint> *vbos;
	vector<GLuint> *textures;
};

#endif
