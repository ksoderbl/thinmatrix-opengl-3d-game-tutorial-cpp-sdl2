#include "FontRenderer.h"

FontRenderer::FontRenderer()
{
	shader = new FontShader();
}

FontRenderer::~FontRenderer()
{
	delete shader;
}

void FontRenderer::render(map<FontType*, vector<GUIText*>*>* texts)
{
	map<FontType*, vector<GUIText*>*>::iterator it;
	prepare();

	for (it = texts->begin(); it != texts->end(); it++) {
		FontType* font = it->first;
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, font->getTextureAtlas());
		for (GUIText* text : *it->second) {
			renderText(text);
		}
	}

	endRendering();
}

void FontRenderer::cleanUp()
{
	shader->cleanUp();
}

void FontRenderer::prepare()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	shader->start();
}

void FontRenderer::renderText(GUIText* text)
{
	glBindVertexArray(text->getMesh());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	shader->loadColor(text->getColor());
	shader->loadTranslation(text->getPosition());
	glDrawArrays(GL_TRIANGLES, 0, text->getVertexCount());
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);
}

void FontRenderer::endRendering()
{
	shader->stop();
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}
