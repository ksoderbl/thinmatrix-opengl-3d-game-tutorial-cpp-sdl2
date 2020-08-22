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
	
	glBindVertexArray(vaoID);
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->getIboID());
	
	glDrawElements(
		GL_TRIANGLES,      // mode
		model->getVertexCount(), //indices.size(),    // count
		GL_UNSIGNED_INT,   // type
		(void*)0           // element array buffer offset
	);
	
	//glDisableVertexAttribArray(0);
	//glBindVertexArray(0);
	
	//glDisableClientState(GL_VERTEX_ARRAY);
}

