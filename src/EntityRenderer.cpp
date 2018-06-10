#include "RawModel.h"
#include "EntityRenderer.h"
#include "DisplayManager.h"

EntityRenderer::EntityRenderer(StaticShader& shader) : shader(shader)
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	createProjectionMatrix();
	shader.start();
	shader.loadProjectionMatrix(projectionMatrix);
	shader.stop();
}

void EntityRenderer::prepare()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0.1, 1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
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

/*
void EntityRenderer::render(Entity& entity, StaticShader& shader)
{
	TexturedModel& model = entity.getModel();
	RawModel& rawModel = model.getRawModel();

	glBindVertexArray(rawModel.getVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

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

	ModelTexture& texture = model.getTexture();
	shader.loadShineVariables(texture.getShineDamper(), texture.getReflectivity());
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, model.getTexture().getID());

	glDrawElements(GL_TRIANGLES, rawModel.getVertexCount(), GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);	
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}
*/

void EntityRenderer::createProjectionMatrix()
{
	// https://www.youtube.com/watch?v=50Y9u7K0PZo#t=7m30s
	// https://www.youtube.com/watch?v=50Y9u7K0PZo#t=10m10s
	// http://www.songho.ca/opengl/gl_projectionmatrix.html

	GLfloat aspectRatio = 1280.0f / 720.0f; // TODO
	GLfloat angle = FOV / 2.0f;
	GLfloat radAngle = glm::radians(angle);
	GLfloat tanAngle = tanf(radAngle);
	GLfloat y_scale = (GLfloat) (1.0f / tanAngle) * aspectRatio;
	GLfloat x_scale = y_scale / aspectRatio;
	GLfloat frustum_length = FAR_PLANE - NEAR_PLANE;

	glm::mat4 m = glm::mat4(1.0f);

	m[0][0] = x_scale;
	m[1][1] = y_scale;
	m[2][2] = -((FAR_PLANE + NEAR_PLANE) / frustum_length);
	m[2][3] = -1;
	m[3][2] = -(2 * NEAR_PLANE * FAR_PLANE) / frustum_length;
	m[3][3] = 0;

	//Maths::printMatrix(m, "proj1");

	//glm::mat4 projectionMatrix2 = glm::perspective(FOV, aspectRatio, NEAR_PLANE, FAR_PLANE);
	//Maths::printMatrix(projectionMatrix2, "proj2");

	projectionMatrix = m;
}
