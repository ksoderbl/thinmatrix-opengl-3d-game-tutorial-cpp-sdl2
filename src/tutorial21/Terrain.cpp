#include "Terrain.h"

Terrain::Terrain(int gridX, int gridZ, Loader &loader,
	TerrainTexturePack &texturePack, TerrainTexture& blendMap, string heightMap)
	: texturePack(texturePack), blendMap(blendMap)
{
	this->position[0] = gridX * SIZE;
	this->position[1] = 0;
	this->position[2] = gridZ * SIZE;
	this->model = generateTerrain(loader, heightMap);
}

RawModel* Terrain::generateTerrain(Loader &loader, string heightMap)
{
	GLint tx_w;       /* width in pixels */
	GLint tx_h;       /* height in pixels */
	GLenum tx_fmt;    /* format: RGB or RGBA */
	GLubyte *tx_data; /* image data */
	string fileName = "../../res/" + heightMap + ".png";

	tx_data = loader.LoadPNGImage(fileName, &tx_w, &tx_h, &tx_fmt);
	if (!tx_data) {
		cerr << "generateTerrain: LoadPNGImage failed for " << fileName << "\n";
		exit(1);
	}
	int VERTEX_COUNT = tx_h; // image.getHeight();

	vector<GLfloat> verticesArray;
	vector<GLfloat> normalsArray;
	vector<GLfloat> textureArray;
	vector<GLuint> indicesArray;

	for (int i = 0; i < VERTEX_COUNT; i++) {
		for (int j = 0; j < VERTEX_COUNT; j++) {
			GLfloat s = ((GLfloat)j) / ((GLfloat)(VERTEX_COUNT - 1));
			GLfloat t = ((GLfloat)i) / ((GLfloat)(VERTEX_COUNT - 1));
			verticesArray.push_back(s * SIZE);
			GLfloat height = getHeight(j, i, tx_w, tx_h, tx_data);
			verticesArray.push_back(height);
			verticesArray.push_back(t * SIZE);
			glm::vec3 normal = calculateNormal(j, i, tx_w, tx_h, tx_data);
			normalsArray.push_back(normal.x);
			normalsArray.push_back(normal.y);
			normalsArray.push_back(normal.z);
			textureArray.push_back(s);
			textureArray.push_back(t);
		}
	}

	for (int gz = 0; gz < VERTEX_COUNT - 1; gz++) {
		for (int gx = 0; gx < VERTEX_COUNT - 1; gx++) {
			GLuint topLeft = (gz * VERTEX_COUNT) + gx;
			GLuint topRight = topLeft + 1;
			GLuint bottomLeft = ((gz + 1) * VERTEX_COUNT) + gx;
			GLuint bottomRight = bottomLeft + 1;
			indicesArray.push_back(topLeft);
			indicesArray.push_back(bottomLeft);
			indicesArray.push_back(topRight);
			indicesArray.push_back(topRight);
			indicesArray.push_back(bottomLeft);
			indicesArray.push_back(bottomRight);
		}
	}
	return loader.loadToVAO(verticesArray, textureArray, normalsArray, indicesArray);
}

glm::vec3 Terrain::calculateNormal(
	int x, int z,
	//BufferedImage& image,
	GLint tx_w,       /* width in pixels */
	GLint tx_h,       /* height in pixels */
	GLubyte *tx_data) /* image data */
{
	GLfloat heightL = getHeight(x-1, z, tx_w, tx_h, tx_data);
	GLfloat heightR = getHeight(x+1, z, tx_w, tx_h, tx_data);
	GLfloat heightD = getHeight(x, z-1, tx_w, tx_h, tx_data);
	GLfloat heightU = getHeight(x, z-1, tx_w, tx_h, tx_data);
	glm::vec3 normal = glm::vec3(heightL-heightR, 2.0f, heightD-heightU);
	normal = glm::normalize(normal);
	return normal;
}

GLfloat Terrain::getHeight(
	int x, int z,
	//BufferedImage& image,
	GLint tx_w,       /* width in pixels */
	GLint tx_h,       /* height in pixels */
	GLubyte *tx_data) /* image data */
{
	//if (x < 0 || x >= image.getHeight() || z < 0 || z >= image.getHeight()) {
	if (x < 0 || x >= tx_w || z < 0 || z >= tx_h) {
		return 0;
	}
	//GLfloat height = image.getRBG(x, z);
	int index = 4 * (x + z * tx_w);
	int r = *(tx_data + index);
	//int g = *(tx_data + index + 1);
	//int b = *(tx_data + index + 2);

	// r should be between 0 and 255;
	GLfloat height = r;
	height -= 127.5;
	height /= 127.5; // should be between -1 and 1
	height *= MAX_HEIGHT;
	return height;
}
