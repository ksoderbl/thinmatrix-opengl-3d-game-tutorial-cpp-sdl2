#include "HeightsGenerator.h"
#include "../toolbox/Maths.h"
#include "../toolbox/Utils.h"

HeightsGenerator::HeightsGenerator(Loader &loader, string heightMap, int stepSize)
{
	this->stepSize = stepSize;
	this->vertexCount = 256 / stepSize;

	if (heightMap != "") {
		string fileName = "../res/" + heightMap + ".png";
		image = loader.decodeTextureFile(fileName);
		if (!image) {
			cerr << "HeightsGenerator: decodeTextureFile failed for " << fileName << "\n";
			exit(1);
		}
		this->vertexCount = image->getHeight() / stepSize;
	}

	cout << "vertexCount: " << this->vertexCount << endl;

	this->seed = 431;
	this->amplitude = 70;
	this->octaves = 4;
	this->roughness = 0.3;
}

/*
GLfloat HeightsGenerator::generateHeight(int x, int z)
{
	if (x < 0 || x >= image->getWidth() || z < 0 || z >= image->getHeight()) {
		return 0;
	}
	//GLfloat height = image.getRBG(x, z);
	int index = 4 * (x + z * image->getWidth());
	int r = *(image->getBuffer() + index);
	//int g = *(tx_data + index + 1);
	//int b = *(tx_data + index + 2);

	// r should be between 0 and 255;
	GLfloat height = r;
	height -= 127.5;
	height /= 127.5; // should be between -1 and 1
	height *= MAX_HEIGHT;
	// get rid of 0 height terrain so it's not at the same level as water
	//if (height > -1.0 && height < 1.0)
	//	height -= 2.0;
	return height;
}
*/

GLfloat HeightsGenerator::generateHeight(int x, int z)
{
	GLfloat total = 0.0f;

	GLfloat d = (GLfloat) (2 << (octaves));

	for (int i = 0; i < octaves; i++) {
		GLfloat freq = (GLfloat) (2 << i) / d;
		GLfloat amp = (GLfloat) pow(roughness, i) * amplitude;
		total += getInterpolatedNoise(x * freq, z * freq) * amp;
	}
	//cout << x << ", " << z << ": " << total << endl;
	return total;
}

GLfloat HeightsGenerator::getInterpolatedNoise(GLfloat x, GLfloat z)
{
	int intX = (int)x;
	int intZ = (int)z;
	float fracX = x - intX;
	float fracZ = z - intZ;

	GLfloat v1 = getSmoothNoise(intX, intZ);
	GLfloat v2 = getSmoothNoise(intX + 1, intZ);
	GLfloat v3 = getSmoothNoise(intX, intZ + 1);
	GLfloat v4 = getSmoothNoise(intX + 1, intZ + 1);
	GLfloat i1 = interpolate(v1, v2, fracX);
	GLfloat i2 = interpolate(v3, v4, fracX);
	return interpolate(i1, i2, fracZ);
}

GLfloat HeightsGenerator::interpolate(GLfloat a, GLfloat b, GLfloat blend)
{
	double theta = blend * M_PI;
	GLfloat f = (GLfloat)(1.0 - cos(theta)) * 0.5f;
	return a * (1.0f - f) + b * f;
}

GLfloat HeightsGenerator::getSmoothNoise(int x, int z)
{
	GLfloat corners = (getNoise(x - 1, z - 1) + getNoise(x + 1, z - 1)
			   + getNoise(x - 1, z + 1) + getNoise(x + 1, z + 1)) / 16.0f;
	GLfloat sides   = (getNoise(x - 1, z)   + getNoise(x + 1, z)
			   + getNoise(x, z + 1) + getNoise(x, z + 1)) / 8.0f;
	GLfloat center  = getNoise(x, z) / 4.0f;
	return corners + sides + center;
}

GLfloat HeightsGenerator::getNoise(int x, int z)
{
	Utils::SeedRand(x * 963 + z * 13251 + seed * 31);
	return Utils::Rand() * 2.0f - 1.0f;
}
