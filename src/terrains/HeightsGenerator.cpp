#include "HeightsGenerator.h"
#include "../toolbox/Maths.h"
#include "../toolbox/Utils.h"

HeightsGenerator::HeightsGenerator(Loader &loader, string heightMap, int stepSize)
{
	string fileName = "../res/" + heightMap + ".png";
	image = loader.decodeTextureFile(fileName);
	if (!image) {
		cerr << "HeightsGenerator: decodeTextureFile failed for " << fileName << "\n";
		exit(1);
	}
	this->stepSize = stepSize;
	this->vertexCount = image->getHeight() / stepSize;
}

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
