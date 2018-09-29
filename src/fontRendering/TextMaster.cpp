#include "TextMaster.h"

#include "TextMeshData.h"

TextMaster textMaster;

TextMaster::TextMaster()
{
	texts = new map<FontType*, vector<GUIText*>*>;
}

void TextMaster::init(Loader* loader)
{
	renderer = new FontRenderer();
	this->loader = loader;
}

void TextMaster::render()
{
	renderer->render(texts);
}

void TextMaster::loadText(GUIText* text)
{
	FontType* font = text->getFont();
	TextMeshData* data = font->loadText(text);
	GLuint vao = loader->loadToVAO(data->getVertexPositions(), data->getTextureCoords());
	text->setMeshInfo(vao, data->getVertexCount());
	vector<GUIText*>* textBatch = nullptr;
	map<FontType*, vector<GUIText*>*>::iterator it = texts->find(font);
	if (it == texts->end()) {
		textBatch = new vector<GUIText*>;
		texts->insert(std::pair<FontType*, vector<GUIText*>*>(font, textBatch));
	} else {
		textBatch = it->second;
	}
	textBatch->push_back(text);

}

void TextMaster::removeText(GUIText* text)
{
	FontType* font = text->getFont();
	
	map<FontType*, vector<GUIText*>*>::iterator it = texts->find(font);
	
	if (it != texts->end()) {
		vector<GUIText*>* textBatch = it->second;
		vector<GUIText*>::iterator vit = std::find(textBatch->begin(), textBatch->end(), text);
		if (vit != textBatch->end()) {
			textBatch->erase(vit);
		}
		if (textBatch->empty()) {
			texts->erase(it);
		}
	}
}

void TextMaster::cleanUp()
{
	renderer->cleanUp();
}
