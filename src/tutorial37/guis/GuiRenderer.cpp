#include "GuiRenderer.h"
#include "../toolbox/Maths.h"

GuiRenderer::GuiRenderer(Loader& loader) : loader(loader)
{
	vector<GLfloat> positions = { -1, 1, -1, -1, 1, 1, 1, -1 };
	quad = loader.loadToVAO(positions, 2);
	shader = new GuiShader();
}

void GuiRenderer::render(vector<GuiTexture*>&guis)
{
	shader->start();
	glBindVertexArray(quad->getVaoID());
	glEnableVertexAttribArray(0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	for (GuiTexture *gui : guis) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, gui->getTextureId());
		glm::mat4 matrix = Maths::createTransformationMatrix(
			gui->getPosition(), gui->getScale());
		shader->loadTransformationMatrix(matrix);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, quad->getVertexCount());		
	}
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	shader->stop();
}

void GuiRenderer::cleanUp()
{
	shader->cleanUp();
}
