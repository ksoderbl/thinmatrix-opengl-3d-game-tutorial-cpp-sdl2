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
