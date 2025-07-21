#include "RawModel.h"
#include "SkyboxRenderer.h"
#include "DisplayManager.h"
#include "MasterRenderer.h"
#include "Maths.h"

SkyboxRenderer::SkyboxRenderer(Loader& loader, glm::mat4& projectionMatrix)
{
	cube = loader.loadToVAO(VERTICES, 3);
	texture = loader.loadCubeMap(TEXTURE_FILES);
	nightTexture = loader.loadCubeMap(NIGHT_TEXTURE_FILES);
	shader = new SkyboxShader();
	shader->start();
	shader->connectTextureUnits();
	shader->loadProjectionMatrix(projectionMatrix);
	shader->stop();
}

void SkyboxRenderer::render(Camera& camera, GLfloat r, GLfloat g, GLfloat b,
	DisplayManager& display)
{
	shader->start();
	shader->loadViewMatrix(camera, display);
	shader->loadFogColor(r, g, b);
	// Disable this, otherwise one side of the sky is clipped from the
	// reflection and refraction textures
	// glDisable(GL_CLIP_DISTANCE0);
	glBindVertexArray(cube->getVaoID());
	glEnableVertexAttribArray(0);
	bindTextures(display);
	glDrawArrays(GL_TRIANGLES, 0, cube->getVertexCount());
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	shader->stop();
}

void SkyboxRenderer::bindTextures(DisplayManager& display)
{
	myTime += display.getFrameTimeSeconds() * 100; // original: * 1000
	while (myTime >= 24000) {
		myTime -= 24000;
	}
	int texture1, texture2;
	GLfloat blendFactor;
	if (myTime < 5000) {
		texture1 = nightTexture;
		texture2 = nightTexture;
		blendFactor = (myTime - 0) / (5000 - 0);
	}
	else if (myTime >= 5000 && myTime < 8000) {
		texture1 = nightTexture;
		texture2 = texture;
		blendFactor = (myTime - 5000) / (8000 - 5000);
	}
	else if (myTime >= 8000 && myTime < 21000) {
		texture1 = texture;
		texture2 = texture;
		blendFactor = (myTime - 8000) / (21000 - 8000);
	}
	else {
		texture1 = texture;
		texture2 = nightTexture;
		blendFactor = (myTime - 21000) / (24000 - 21000);
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture2);
	shader->loadBlendFactor(blendFactor);
}
