#ifndef TEXTMASTER_H
#define TEXTMASTER_H

#include "../Headers.h"
#include "../Loader.h"

#include "FontType.h"
#include "GUIText.h"
#include "FontRenderer.h"

class TextMaster {
public:
	TextMaster();
	void init(Loader* loader);
	void loadText(GUIText* text);
	void render();
	
	
	void removeText(GUIText* text);
	void cleanUp();
private:
	Loader* loader;
	map<FontType*, vector<GUIText*>*>* texts;
	FontRenderer* renderer;
};

// global variable
extern TextMaster textMaster;

#endif
