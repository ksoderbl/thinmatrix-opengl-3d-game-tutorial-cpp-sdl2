#ifndef FONTRENDERER_H
#define FONTRENDERER_H

#include "../Headers.h"

#include "FontType.h"
#include "GUIText.h"
#include "FontShader.h"


class FontRenderer {
public:
	FontRenderer();
	~FontRenderer();
	void render(map<FontType*, vector<GUIText*>*>* texts);
	void cleanUp();
	void prepare();
	void renderText(GUIText* text);
	void endRendering();
private:
	FontShader *shader;
};

#endif
