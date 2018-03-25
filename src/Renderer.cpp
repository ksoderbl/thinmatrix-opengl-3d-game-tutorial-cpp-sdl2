
#include "Headers.h"
#include "RawModel.h"
#include "Renderer.h"

void Renderer::prepare()
{
	glClearColor(1, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::render(RawModel *model)
{
	GLuint vaoID = model->getVaoID();
	
	//glEnableClientState(GL_VERTEX_ARRAY);
	
	glUseProgram(model->getShaderProgram());
	glBindVertexArray(vaoID);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, model->getVertexCount());
	
	//glDisableVertexAttribArray(0);
	//glBindVertexArray(0);
	
	//glDisableClientState(GL_VERTEX_ARRAY);
}

