#include "../models/RawModel.h"
#include "ParticleRenderer.h"
#include "../renderEngine/DisplayManager.h"
#include "../toolbox/Maths.h"

ParticleRenderer::ParticleRenderer(Loader& loader, glm::mat4& projectionMatrix) : loader(loader)
{
	buffer.resize(INSTANCE_DATA_LENGTH * MAX_INSTANCES);
	vboID = loader.createEmptyVbo(buffer);
	vector<GLfloat> vertices = { -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, -0.5f };
	quad = loader.loadToVAO(vertices, 2);
	// modelViewMatrix
	loader.addInstancedAttribute(quad->getVaoID(), vboID, 1, 4, INSTANCE_DATA_LENGTH, 0);
	loader.addInstancedAttribute(quad->getVaoID(), vboID, 2, 4, INSTANCE_DATA_LENGTH, 4);
	loader.addInstancedAttribute(quad->getVaoID(), vboID, 3, 4, INSTANCE_DATA_LENGTH, 8);
	loader.addInstancedAttribute(quad->getVaoID(), vboID, 4, 4, INSTANCE_DATA_LENGTH, 12);
	// texOffsets
	loader.addInstancedAttribute(quad->getVaoID(), vboID, 5, 4, INSTANCE_DATA_LENGTH, 16);
	// blendFactor
	loader.addInstancedAttribute(quad->getVaoID(), vboID, 6, 1, INSTANCE_DATA_LENGTH, 20);
	shader.start();
	shader.loadProjectionMatrix(projectionMatrix);
	shader.stop();
}


void ParticleRenderer::render(map<ParticleTexture*, vector<Particle>>& particlesMap, Camera& camera)
{
	glm::mat4 viewMatrix = Maths::createViewMatrix(camera);

	prepare();

	for (auto mit = particlesMap.begin();  mit != particlesMap.end(); mit++) {
		ParticleTexture* texture = mit->first;
		vector<Particle>& particles = mit->second;
		bindTexture(texture);
		pointer = 0;
		vector<GLfloat> vboData(particles.size() * INSTANCE_DATA_LENGTH);

		for (auto vit = particles.begin(); vit != particles.end(); vit++) {
			Particle& particle = *vit;

			updateModelViewMatrix(particle.getPosition(), particle.getRotation(),
					      particle.getScale(), viewMatrix, vboData);
			updateTexCoordInfo(particle, vboData);
		}
		loader.updateVbo(vboID, vboData);
		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, quad->getVertexCount(), particles.size());

	}

	finishRendering();
}

void ParticleRenderer::cleanUp()
{
	shader.cleanUp();
}

void ParticleRenderer::updateTexCoordInfo(Particle& particle, vector<GLfloat>& vboData)
{
	vboData[pointer++] = particle.getTexOffset1().x;
	vboData[pointer++] = particle.getTexOffset1().y;
	vboData[pointer++] = particle.getTexOffset2().x;
	vboData[pointer++] = particle.getTexOffset2().y;
	vboData[pointer++] = particle.getBlend();
}

void ParticleRenderer::bindTexture(ParticleTexture* texture)
{
	if (texture->isAdditive()) {
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	} else {
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->getTextureId());
	shader.loadNumberOfRows(texture->getNumberOfRows());
}

void ParticleRenderer::updateModelViewMatrix(
	glm::vec3& position, GLfloat rotation, GLfloat scale, glm::mat4& viewMatrix,
	vector<GLfloat>& vboData)
{
	glm::mat4 unit = glm::mat4(1.0f);
	glm::mat4 modelMatrix = glm::translate(unit, position);
	// Set the rotation 3x3 part of the model matrix to the
	// transpose of the 3x3 rotation part of the view matrix.
	modelMatrix[0][0] = viewMatrix[0][0];
	modelMatrix[0][1] = viewMatrix[1][0];
	modelMatrix[0][2] = viewMatrix[2][0];
	modelMatrix[1][0] = viewMatrix[0][1];
	modelMatrix[1][1] = viewMatrix[1][1];
	modelMatrix[1][2] = viewMatrix[2][1];
	modelMatrix[2][0] = viewMatrix[0][2];
	modelMatrix[2][1] = viewMatrix[1][2];
	modelMatrix[2][2] = viewMatrix[2][2];
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(scale));
	glm::mat4 modelViewMatrix = viewMatrix * modelMatrix;
	storeMatrixData(modelViewMatrix, vboData);
}

void ParticleRenderer::storeMatrixData(glm::mat4& matrix, vector<GLfloat>& vboData)
{
	vboData[pointer++] = matrix[0][0];
	vboData[pointer++] = matrix[0][1];
	vboData[pointer++] = matrix[0][2];
	vboData[pointer++] = matrix[0][3];
	vboData[pointer++] = matrix[1][0];
	vboData[pointer++] = matrix[1][1];
	vboData[pointer++] = matrix[1][2];
	vboData[pointer++] = matrix[1][3];
	vboData[pointer++] = matrix[2][0];
	vboData[pointer++] = matrix[2][1];
	vboData[pointer++] = matrix[2][2];
	vboData[pointer++] = matrix[2][3];
	vboData[pointer++] = matrix[3][0];
	vboData[pointer++] = matrix[3][1];
	vboData[pointer++] = matrix[3][2];
	vboData[pointer++] = matrix[3][3];
}

void ParticleRenderer::prepare()
{
	shader.start();
	glBindVertexArray(quad->getVaoID());
	for (GLuint i = 0; i <= 6; i++) {
		glEnableVertexAttribArray(i);
	}
	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);

}

void ParticleRenderer::finishRendering()
{
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
	for (GLuint i = 0; i <= 6; i++) {
		glDisableVertexAttribArray(i);
	}
	glBindVertexArray(0);
	shader.stop();
}
