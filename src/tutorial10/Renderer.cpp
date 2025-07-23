#include "Headers.h"
#include "RawModel.h"
#include "Renderer.h"
#include "DisplayManager.h"

Renderer::Renderer(StaticShader& shader)
{
	createProjectionMatrix();
	shader.start();
	shader.loadProjectionMatrix(projectionMatrix);
	shader.stop();
}

void Renderer::prepare()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0.5, 1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(Entity& entity, StaticShader& shader)
{
	TexturedModel& texturedModel = entity.getModel();
	RawModel& model = texturedModel.getRawModel();

	glBindVertexArray(model.getVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
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
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturedModel.getTexture().getID());
	glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);	
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);
}

void Renderer::createProjectionMatrix()
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
