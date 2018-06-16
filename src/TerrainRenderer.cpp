#include "RawModel.h"
#include "TerrainRenderer.h"
#include "DisplayManager.h"

TerrainRenderer::TerrainRenderer(TerrainShader& shader, glm::mat4& projectionMatrix) : shader(shader)
{
	shader.start();
	shader.loadProjectionMatrix(projectionMatrix);
	shader.stop();
}

void TerrainRenderer::render(vector<Terrain*>* terrains)
{
	for (vector<Terrain*>::iterator it = terrains->begin();
		it != terrains->end();
		it++) {
		Terrain* terrain = *it;
		prepareTerrain(*terrain);
		loadModelMatrix(*terrain);
		glDrawElements(GL_TRIANGLES, terrain->getModel().getVertexCount(), GL_UNSIGNED_INT, 0);
		unbindTexturedModel();
	}
}

void TerrainRenderer::prepareTerrain(Terrain& terrain)
{
	RawModel& rawModel = terrain.getModel();
	glBindVertexArray(rawModel.getVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	ModelTexture& texture = terrain.getTexture();
	shader.loadShineVariables(texture.getShineDamper(), texture.getReflectivity());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.getID());
}

void TerrainRenderer::unbindTexturedModel()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void TerrainRenderer::loadModelMatrix(Terrain& terrain)
{
	glm::mat4 transformationMatrix = Maths::createTransformationMatrix(
		terrain.getPosition(), 0.0f, 0.0f, 0.0f, 1.0f);

	//glm::vec3 pos = entity.getPosition();
	//cout << "pos = " << pos[0] << ", " << pos[1] << ", " << pos[2] << endl;
	//glm::mat4 t = glm::translate(glm::mat4(1.0f), pos);
	//Maths::printMatrix(t, "t");
	//Maths::printMatrix(transformationMatrix, "T");

	shader.loadTransformationMatrix(transformationMatrix);
}

