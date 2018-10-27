#include "Terrain.h"
#include "../toolbox/Maths.h"

Terrain::Terrain(int gridX, int gridZ, Loader &loader,
	TerrainTexturePack &texturePack, TerrainTexture& blendMap, string heightMap)
	: texturePack(texturePack), blendMap(blendMap)
{
	this->position.x = gridX * SIZE;
	this->position.y = 0;
	this->position.z = gridZ * SIZE;
	this->model = generateTerrain(loader, heightMap);
}

GLfloat Terrain::getHeightOfTerrain(GLfloat worldX, GLfloat worldZ)
{
	GLfloat terrainX = worldX - this->position.x;
	GLfloat terrainZ = worldZ - this->position.z;
	GLfloat gridSquareSize = SIZE / ((GLfloat)heightsLength - 1);
	int gridX = (int) floor(terrainX / gridSquareSize);
	int gridZ = (int) floor(terrainZ / gridSquareSize);
	if (gridX >= heightsLength - 1 || gridZ >= heightsLength - 1 || gridX < 0 || gridZ < 0) {
		return 0;
	}
	GLfloat xCoord = fmod(terrainX, gridSquareSize) / gridSquareSize;
	GLfloat zCoord = fmod(terrainZ, gridSquareSize) / gridSquareSize;
	GLfloat answer;
	glm::vec3 topLeft(0.0f, heights[gridX][gridZ], 0.0f);
	glm::vec3 topRight(1.0f, heights[gridX + 1][gridZ], 0.0f);
	glm::vec3 bottomLeft(0.0f, heights[gridX][gridZ + 1], 1.0f);
	glm::vec3 bottomRight(1.0f, heights[gridX + 1][gridZ + 1], 1.0f);
	glm::vec2 pos(xCoord, zCoord);
	if (xCoord <= (1 - zCoord)) {
		answer = Maths::barycentric(topLeft, topRight, bottomLeft, pos);
	} else {
		answer = Maths::barycentric(topRight, bottomRight, bottomLeft, pos);
	}
	return answer;
}

RawModel* Terrain::generateTerrain(Loader &loader, string heightMap)
{
	int stepSize = 4;

	HeightsGenerator generator(loader, heightMap, stepSize);

	int vertexCount = generator.getVertexCount();

	// dynamically create 2 dimensional array
	heights = new GLfloat* [vertexCount];
	for (int i = 0; i < vertexCount; i++) {
		heights[i] = new GLfloat [vertexCount];
	}
	heightsLength = vertexCount;

	vector<GLfloat> verticesArray;
	vector<GLfloat> normalsArray;
	vector<GLfloat> textureArray;
	vector<GLuint> indicesArray;

	for (int i = 0; i < vertexCount; i++) {
		for (int j = 0; j < vertexCount; j++) {
			GLfloat s = ((GLfloat)j) / ((GLfloat)(vertexCount - 1));
			GLfloat t = ((GLfloat)i) / ((GLfloat)(vertexCount - 1));
			verticesArray.push_back(s * SIZE);
			//GLfloat height = getHeight(j * stepSize, i * stepSize, stepSize, image);
			GLfloat height = getHeight(j * stepSize, i * stepSize, stepSize, generator);
			heights[j][i] = height;
			verticesArray.push_back(height);
			verticesArray.push_back(t * SIZE);
			glm::vec3 normal = calculateNormal(j * stepSize, i * stepSize, stepSize, generator);
			normalsArray.push_back(normal.x);
			normalsArray.push_back(normal.y);
			normalsArray.push_back(normal.z);
			textureArray.push_back(s);
			textureArray.push_back(t);
		}
	}

	for (int gz = 0; gz < vertexCount - 1; gz++) {
		for (int gx = 0; gx < vertexCount - 1; gx++) {
			GLuint topLeft = (gz * vertexCount) + gx;
			GLuint topRight = topLeft + 1;
			GLuint bottomLeft = ((gz + 1) * vertexCount) + gx;
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

glm::vec3 Terrain::calculateNormal(int x, int z, int stepSize, HeightsGenerator& generator)
{
	GLfloat heightL = getHeight(x-stepSize, z, stepSize, generator);
	GLfloat heightR = getHeight(x+stepSize, z, stepSize, generator);
	GLfloat heightD = getHeight(x, z-stepSize, stepSize, generator);
	GLfloat heightU = getHeight(x, z-stepSize, stepSize, generator);
	glm::vec3 normal = glm::vec3(heightL-heightR, 2.0f * stepSize, heightD-heightU);
	normal = glm::normalize(normal);
	return normal;
}

GLfloat Terrain::getHeight(int x, int z, int stepSize, HeightsGenerator& generator)
{
	return generator.generateHeight(x, z);
}
