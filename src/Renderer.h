#ifndef RENDERER_H
#define RENDERER_H

#include "TexturedModel.h"
#include "Entity.h"
#include "StaticShader.h"

class Renderer {
public:
	void prepare();
	void render(Entity *entity, StaticShader *shader);
private:
	
};

#endif
