#include "../models/RawModel.h"
#include "ParticleRenderer.h"
#include "../DisplayManager.h"
#include "../Maths.h"

ParticleRenderer::ParticleRenderer(Loader& loader, glm::mat4& projectionMatrix)
{
	vector<GLfloat> vertices = { -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, -0.5f };
	quad = loader.loadToVAO(vertices, 2);
	shader = new ParticleShader();
	shader->start();
	shader->loadProjectionMatrix(projectionMatrix);
	shader->stop();
}


void ParticleRenderer::render(vector<Particle>& particles, Camera& camera)
{
	glm::mat4 viewMatrix = Maths::createViewMatrix(camera);
	prepare();

	auto it = particles.begin();
	while (it != particles.end()) {
		Particle& particle = *it;
		updateModelViewMatrix(particle.getPosition(), particle.getRotation(),
				      particle.getScale(), viewMatrix);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, quad->getVertexCount());
		it++;
	}
	finishRendering();
}

void ParticleRenderer::cleanUp()
{
	shader->cleanUp();
}

void ParticleRenderer::updateModelViewMatrix(
	glm::vec3& position, GLfloat rotation, GLfloat scale, glm::mat4& viewMatrix)
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
	shader->loadModelViewMatrix(modelViewMatrix);
}

void ParticleRenderer::prepare()
{
	shader->start();
	glBindVertexArray(quad->getVaoID());
	glEnableVertexAttribArray(0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);

}

void ParticleRenderer::finishRendering()
{
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	shader->stop();
}
