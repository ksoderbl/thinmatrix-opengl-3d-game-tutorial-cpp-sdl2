#include "WaterFrameBuffers.h"
#include "Maths.h"

WaterFrameBuffers::WaterFrameBuffers(DisplayManager &display) : display(display)
{
	initializeReflectionFrameBuffer();
	initializeRefractionFrameBuffer();
}

void WaterFrameBuffers::cleanUp()
{
	glDeleteFramebuffers(1, &reflectionFrameBufferID);
	glDeleteTextures(1, &reflectionTextureID);
	glDeleteRenderbuffers(1, &reflectionDepthBufferID);
	glDeleteFramebuffers(1, &refractionFrameBufferID);
	glDeleteTextures(1, &refractionTextureID);
	glDeleteTextures(1, &refractionDepthTextureID);
}

// call before rendering to this FBO
void WaterFrameBuffers::bindReflectionFrameBuffer()
{
	bindFrameBuffer(reflectionFrameBufferID, REFLECTION_WIDTH, REFLECTION_HEIGHT);
}

// call before rendering to this FBO
void WaterFrameBuffers::bindRefractionFrameBuffer()
{
	bindFrameBuffer(refractionFrameBufferID, REFRACTION_WIDTH, REFRACTION_HEIGHT);
}

// switch back to default framebuffer
void WaterFrameBuffers::unbindCurrentFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, display.getWidth(), display.getHeight());
}

void WaterFrameBuffers::initializeReflectionFrameBuffer()
{
	reflectionFrameBufferID = createFrameBuffer();
	reflectionTextureID = createTextureAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
	reflectionDepthBufferID = createDepthBufferAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
	unbindCurrentFrameBuffer();
}

void WaterFrameBuffers::initializeRefractionFrameBuffer()
{
	refractionFrameBufferID = createFrameBuffer();
	refractionTextureID = createTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
	refractionDepthTextureID = createDepthTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
	unbindCurrentFrameBuffer();
}

void WaterFrameBuffers::bindFrameBuffer(GLuint framebufferID,
	GLint width, GLint height)
{
	// make sure texture isn't bound
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);
	glViewport(0, 0, width, height);
}

GLuint WaterFrameBuffers::createFrameBuffer()
{
	GLuint framebufferID;
	glGenFramebuffers(1, &framebufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	return framebufferID;
}

GLuint WaterFrameBuffers::createTextureAttachment(GLint width, GLint height)
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureID, 0);
	return textureID;
}

GLuint WaterFrameBuffers::createDepthTextureAttachment(GLint width, GLint height)
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 
		0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, textureID, 0);
	return textureID;
}

GLuint WaterFrameBuffers::createDepthBufferAttachment(GLint width, GLint height)
{
	GLuint depthbufferID;
	glGenRenderbuffers(1, &depthbufferID);
	glBindRenderbuffer(GL_RENDERBUFFER, depthbufferID);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
		GL_RENDERBUFFER, depthbufferID);
	return depthbufferID;
}


/*
WaterFrameBuffers::WaterFrameBuffers(
	Loader& loader,
	WaterShader& shader,
	glm::mat4& projectionMatrix) : shader(shader)
{
	shader.start();
	shader.loadProjectionMatrix(projectionMatrix);
	shader.stop();
	setUpVAO(loader);
}

void WaterFrameBuffers::render(vector<WaterTile*>& water, Camera& camera)
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

void WaterFrameBuffers::prepareRender(Camera& camera)
{
	shader.start();
	shader.loadViewMatrix(camera);
	glBindVertexArray(quad->getVaoID());
	glEnableVertexAttribArray(0);
}

void WaterFrameBuffers::unbind()
{
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	shader.stop();
}

void WaterFrameBuffers::setUpVAO(Loader& loader)
{
	// Just x and z vertex positions, y is set in shader
	vector<GLfloat> vertices = { -1, -1, -1, 1, 1, -1, 1, -1, -1, 1, 1, 1 };
	quad = loader.loadToVAO(vertices);
}
*/
