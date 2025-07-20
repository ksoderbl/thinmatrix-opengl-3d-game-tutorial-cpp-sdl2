#include "HeightsGenerator.h"
#include "../toolbox/Maths.h"
#include "../toolbox/Utils.h"

#include <unistd.h>

HeightsGenerator::HeightsGenerator(Loader &loader, string heightMap, int stepSize)
{
	this->stepSize = stepSize;
	this->vertexCount = 256 / stepSize;

	cout << "vertexCount: " << this->vertexCount << endl;
	cout << "stepSize: " << this->stepSize << endl;

	this->image = nullptr;
	if (heightMap != "") {
		string fileName = RES_LOC + heightMap + ".png";
		this->image = loader.decodeTextureFile(fileName);
		if (!this->image) {
			cerr << "HeightsGenerator: decodeTextureFile failed for " << fileName << "\n";
			exit(1);
		}
		this->imageVertexCount = this->image->getHeight();
		cout << "image vertexCount: " << this->imageVertexCount << endl;
		this->imageStepSize = this->imageVertexCount / this->vertexCount;
		if (this->imageStepSize < 1) {
			this->imageStepSize = 1;
		}
		cout << "image stepSize: " << this->imageStepSize << endl;
	}

	this->seed = 431;
	this->amplitude = 70;
	this->octaves = 4;
	this->roughness = 0.3;

	this->xmin = INT_MAX;
	this->xmax = INT_MIN;
	this->zmin = INT_MAX;
	this->zmax = INT_MIN;
	this->getNoiseCalls = 0;
	this->getSmoothNoiseCalls = 0;
	this->getInterpolatedNoiseCalls = 0;

	// generate noise table
	noiseTable = new vector<GLfloat>;

	for (int z = -stepSize; z < vertexCount * stepSize + stepSize; z++) {
		for (int x = -stepSize; x < vertexCount * stepSize + stepSize; x++) {
			noiseTable->push_back(getNoise1(x, z));
		}
	}

	cout << "size of noise table: " << noiseTable->size() << endl;
	cout << "should be: " << (vertexCount + 2) * ( vertexCount + 2) * stepSize * stepSize << endl;
}

void HeightsGenerator::getInfo()
{
	cout << "xmin: " << xmin << endl;
	cout << "xmax: " << xmax << endl;
	cout << "zmin: " << zmin << endl;
	cout << "zmax: " << zmax << endl;
	cout << "getNoise() calls: " << this->getNoiseCalls << endl;
	cout << "getNoise1() calls: " << this->getNoise1Calls << endl;
	cout << "getSmoothNoise() calls: " << this->getSmoothNoiseCalls << endl;
	cout << "getInterpolatedNoise() calls: " << this->getInterpolatedNoiseCalls << endl;

	delete noiseTable;
}

GLfloat HeightsGenerator::getHeightFromImage(int x, int z)
{
	if (this->image == nullptr) {
		return 0;
	}
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

// public
GLfloat HeightsGenerator::generateHeight(int x, int z)
{
	int imageX = x * imageStepSize;
	int imageZ = z * imageStepSize;

	x *= stepSize;
	z *= stepSize;

	GLfloat total = 0.0f;

	//GLfloat d = (GLfloat) (2 << (octaves+2));
	GLfloat d = (GLfloat) (2 << (octaves));

	for (int i = 0; i < octaves; i++) {
		GLfloat freq = (GLfloat) (2 << i) / d;
		GLfloat amp = (GLfloat) pow(roughness, i) * amplitude;
		total += getInterpolatedNoise(x * freq, z * freq) * amp;
	}

	GLfloat heightFromImage = getHeightFromImage(imageX, imageZ);

	//cout << "generateHeight x, z = " << x << ", " << z << ", total: " << total << ", heightFromImage = " << heightFromImage << endl;
	total += heightFromImage;

	return total;
}

GLfloat HeightsGenerator::getInterpolatedNoise(GLfloat x, GLfloat z)
{
	getInterpolatedNoiseCalls++;
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
	getSmoothNoiseCalls++;
	GLfloat corners = (getNoise(x - 1, z - 1) + getNoise(x + 1, z - 1)
			   + getNoise(x - 1, z + 1) + getNoise(x + 1, z + 1)) / 16.0f;
	GLfloat sides   = (getNoise(x - 1, z)   + getNoise(x + 1, z)
			   + getNoise(x, z + 1) + getNoise(x, z + 1)) / 8.0f;
	GLfloat center  = getNoise(x, z) / 4.0f;
	GLfloat result = corners + sides + center;
	//cout << "getSmoothNoise x, z = " << x << ", " << z << ", result = " << result << endl;
	return result;
}

GLfloat HeightsGenerator::getNoise(int x, int z)
{
	getNoiseCalls++;

	// calculate index in noiseTable
	int valuesPerRow = 2 * stepSize + vertexCount * stepSize;
	int ind = x + stepSize; // -stepSize becomes 0
	ind += (z + stepSize) * valuesPerRow;

	GLfloat value = (*noiseTable)[ind];
	/*
	GLfloat value1 = getNoise1(x, z);

	GLfloat diff = value - value1;
	if (diff < 0) {
		diff = -diff;
	}

	if (diff >= 0.001) {
		cout << "getNoise x, z = " << x << ", " << z << ", value = " << value << ", getNoise1() = " << value1 << endl;
		//sleep(1);
	}
	*/

	return value;
}

GLfloat HeightsGenerator::getNoise1(int x, int z)
{
	if (x < xmin) {
		xmin = x;
	}
	if (x > xmax) {
		xmax = x;
	}
	if (z < zmin) {
		zmin = z;
	}
	if (z > zmax) {
		zmax = z;
	}

	getNoise1Calls++;
	Utils::SeedRand(x * 963 + z * 13251 + seed * 31);
	return Utils::Rand() * 2.0f - 1.0f;
}
