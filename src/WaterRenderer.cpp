#include "WaterRenderer.h"
#include "Maths.h"

WaterRenderer::WaterRenderer(
	Loader& loader,
	WaterShader& shader,
	glm::mat4& projectionMatrix) : shader(shader)
{
	shader.start();
	shader.loadProjectionMatrix(projectionMatrix);
	shader.stop();
	setUpVAO(loader);
}

void WaterRenderer::render(vector<WaterTile*>& water, Camera& camera)
{
	prepareRender(camera);
	for (WaterTile* tile : water) {
		glm::vec3 position(tile->getX(), tile->getHeight(), tile->getZ());
		glm::mat4 modelMatrix = Maths::createTransformationMatrix(
			position, 0.0f, 0.0f, 0.0f, WaterTile::TILE_SIZE);
		shader.loadModelMatrix(modelMatrix);
		glDrawArrays(GL_TRIANGLES, 0, quad->getVertexCount());
	}
	unbind();
}

void WaterRenderer::prepareRender(Camera& camera)
{
	shader.start();
	shader.loadViewMatrix(camera);
	glBindVertexArray(quad->getVaoID());
	glEnableVertexAttribArray(0);
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
	quad = loader.loadToVAO(vertices /*, 2*/);
}
