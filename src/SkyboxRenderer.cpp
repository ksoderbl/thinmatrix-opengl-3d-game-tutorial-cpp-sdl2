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
	glDisable(GL_CLIP_DISTANCE0);
	glBindVertexArray(cube->getVaoID());
	glEnableVertexAttribArray(0);
	bindTextures();
	glDrawArrays(GL_TRIANGLES, 0, cube->getVertexCount());
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	shader->stop();
}

void SkyboxRenderer::bindTextures()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, nightTexture);
	shader->loadBlendFactor(0.5);
}
