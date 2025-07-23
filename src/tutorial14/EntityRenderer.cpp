#include "RawModel.h"
#include "EntityRenderer.h"
#include "DisplayManager.h"

EntityRenderer::EntityRenderer(StaticShader& shader, glm::mat4& projectionMatrix) : shader(shader)
{
	shader.start();
	shader.loadProjectionMatrix(projectionMatrix);
	shader.stop();
}

void EntityRenderer::render(std::map<TexturedModel*, vector<Entity*>*>* entities)
{
	for (std::map<TexturedModel*, vector<Entity*>*>::iterator it = entities->begin();
		it != entities->end();
		it++) {
    	TexturedModel* model = (*it).first;

    	prepareTexturedModel(*model);

    	it = entities->find(model);
  		if (it != entities->end()) {
  			vector<Entity*>* batch = it->second;

  			for (vector<Entity*>::iterator vit = batch->begin();
  				vit != batch->end();
  				vit++) {
  				Entity *entity = *vit;
  				prepareInstance(*entity);
  				glDrawElements(GL_TRIANGLES, model->getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);
  			}
  		}

  		unbindTexturedModel();
    }
}

void EntityRenderer::prepareTexturedModel(TexturedModel &model)
{
	RawModel& rawModel = model.getRawModel();

	glBindVertexArray(rawModel.getVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	ModelTexture& texture = model.getTexture();
	shader.loadShineVariables(texture.getShineDamper(), texture.getReflectivity());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, model.getTexture().getID());
}

void EntityRenderer::unbindTexturedModel()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void EntityRenderer::prepareInstance(Entity &entity)
{
	glm::mat4 transformationMatrix = Maths::createTransformationMatrix(
		entity.getPosition(),
		entity.getRotX(), entity.getRotY(), entity.getRotZ(),
		entity.getScale());

	//glm::vec3 pos = entity.getPosition();
	//cout << "pos = " << pos[0] << ", " << pos[1] << ", " << pos[2] << endl;
	//glm::mat4 t = glm::translate(glm::mat4(1.0f), pos);
	//Maths::printMatrix(t, "t");
	//Maths::printMatrix(transformationMatrix, "T");

	shader.loadTransformationMatrix(transformationMatrix);
}

