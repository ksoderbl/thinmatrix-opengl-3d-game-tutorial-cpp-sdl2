#ifndef LOADER_H
#define LOADER_H

#include "Headers.h"
#include "RawModel.h"
#include "TextureData.h"

class Loader {
public:
	Loader();
	~Loader();
	RawModel* loadToVAO(
		vector<GLfloat>&positions,
		vector<GLfloat>&textureCoords,
		vector<GLfloat>&normals,
		vector<GLuint>&indices);
	RawModel* loadToVAO(
		vector<GLfloat>&positions,
		vector<GLfloat>&textureCoords,
		vector<GLfloat>&normals,
		vector<GLfloat>&tangents,
		vector<GLuint>&indices);
	RawModel *loadToVAO(vector<GLfloat>&positions, int dimensions);
	GLuint loadToVAO(vector<GLfloat>&positions, vector<GLfloat>&textureCoords);
	GLuint loadGameTexture(string fileName);
	GLuint loadFontTextureAtlas(string fileName);
	GLubyte* LoadPNGImage(string imageFile, GLsizei *width, GLsizei *height, GLenum *format);
	TextureData* decodeTextureFile(string fileName);
	GLuint loadCubeMap(vector<string>& textureFiles);

	void cleanUp();
private:
	GLuint createVAO();
	GLuint createVBO(GLenum target);
	void storeDataInAttributeList(int attributeNumber, int coordinateSize, vector<GLfloat>&data);
	void unbindVAO();
	void bindIndicesBuffer(vector<GLuint>&indices);
	GLuint loadTexture(string fileName, GLfloat lodBias);

	vector<GLuint> *vaos;
	vector<GLuint> *vbos;
	vector<GLuint> *textures;

	bool useMipMap;
};

#endif
