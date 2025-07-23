#ifndef GUIRENDERER_H
#define GUIRENDERER_H

#include "../Headers.h"
#include "../Loader.h"
#include "GuiTexture.h"
#include "GuiShader.h"

class GuiRenderer {
public:
	GuiRenderer(Loader& loader);
	void render(vector<GuiTexture*>&guis);
	void cleanUp();
private:
	Loader& loader;
	RawModel *quad;
	GuiShader *shader;
};

#endif
