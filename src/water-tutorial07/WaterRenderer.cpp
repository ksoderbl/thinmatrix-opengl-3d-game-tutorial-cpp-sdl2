#include "WaterRenderer.h"
#include "Maths.h"
#include "MasterRenderer.h"

WaterRenderer::WaterRenderer(
	Loader& loader,
	WaterShader& shader,
	glm::mat4& projectionMatrix,
	WaterFrameBuffers& fbos) : shader(shader), fbos(fbos)
{
	dudvTexture = loader.loadTexture(DUDV_MAP);
	normalMap = loader.loadTexture(NORMAL_MAP);
	shader.start();
	shader.connectTextureUnits();
	shader.loadProjectionMatrix(projectionMatrix);
	shader.loadSkyColor(MasterRenderer::SKY_RED, MasterRenderer::SKY_GREEN, MasterRenderer::SKY_BLUE);
	shader.stop();
	setUpVAO(loader);
}

void WaterRenderer::render(vector<WaterTile*>& water, Camera& camera, Light& sun, DisplayManager& display)
{
	prepareRender(camera, sun, display);
	for (WaterTile* tile : water) {
		glm::vec3 position(tile->getX(), tile->getHeight(), tile->getZ());
		glm::mat4 modelMatrix = Maths::createTransformationMatrix(
			position, 0.0f, 0.0f, 0.0f, WaterTile::TILE_SIZE);
		shader.loadModelMatrix(modelMatrix);
		glDrawArrays(GL_TRIANGLES, 0, quad->getVertexCount());
	}
	unbind();
}

void WaterRenderer::prepareRender(Camera& camera, Light& sun, DisplayManager& display)
{
	shader.start();
	shader.loadViewMatrix(camera);
	moveFactor += WAVE_SPEED * display.getFrameTimeSeconds();
	moveFactor = fmod(moveFactor, 1.0);
	shader.loadMoveFactor(moveFactor);
	shader.loadLight(sun);
	glBindVertexArray(quad->getVaoID());
	glEnableVertexAttribArray(0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, fbos.getReflectionTexture());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, fbos.getRefractionTexture());
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, dudvTexture);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, normalMap);
}

void WaterRenderer::unbind()
{
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	shader.stop();
}

void WaterRenderer::setUpVAO(Loader& loader)
{
	// Just x and z vertex positions, y is set in shader
	vector<GLfloat> vertices = { -1, -1, -1, 1, 1, -1, 1, -1, -1, 1, 1, 1 };
	quad = loader.loadToVAO(vertices, 2);
}
