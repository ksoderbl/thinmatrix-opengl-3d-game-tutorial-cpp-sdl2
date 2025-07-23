#include "RawModel.h"
#include "TerrainRenderer.h"
#include "DisplayManager.h"
#include "Maths.h"

TerrainRenderer::TerrainRenderer(TerrainShader& shader, glm::mat4& projectionMatrix) : shader(shader)
{
	shader.start();
	shader.loadProjectionMatrix(projectionMatrix);
	shader.connectTextureUnits();
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
	bindTextures(terrain);
	shader.loadShineVariables(1, 0);
}

void TerrainRenderer::bindTextures(Terrain& terrain)
{
	TerrainTexturePack& texturePack = terrain.getTexturePack();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturePack.getBackgroundTexture().getTextureId());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texturePack.getrTexture().getTextureId());
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texturePack.getgTexture().getTextureId());
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, texturePack.getbTexture().getTextureId());
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, terrain.getBlendMap().getTextureId());
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

