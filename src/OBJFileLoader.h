#ifndef OBJFILELOADER_H
#define OBJFILELOADER_H

#include "Headers.h"
#include "Loader.h"
#include "Vertex.h"
#include "ModelData.h"

class OBJFileLoader {
public:
	ModelData *loadOBJ(string objFileName);
private:
	void removeUnusedVertices(vector<Vertex>& vertices);
};

#endif
