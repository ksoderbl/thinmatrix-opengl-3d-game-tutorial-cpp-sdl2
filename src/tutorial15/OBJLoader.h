#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "Headers.h"
#include "RawModel.h"
#include "Loader.h"

class OBJLoader {
public:
	RawModel *loadObjModel(string fileName, Loader& loader);
};

#endif
