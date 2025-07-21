#ifndef WATERFRAMEBUFFERS_H
#define WATERFRAMEBUFFERS_H

#include "Headers.h"
#include "DisplayManager.h"

class WaterFrameBuffers {
public:
	WaterFrameBuffers(DisplayManager &display);
	void cleanUp();
	void bindReflectionFrameBuffer();
	void bindRefractionFrameBuffer();
	void unbindCurrentFrameBuffer();
	GLuint getReflectionTexture() { return reflectionTextureID; }
	GLuint getRefractionTexture() { return refractionTextureID; }
	GLuint getRefractionDepthTexture() { return refractionDepthTextureID; }
	
private:
	DisplayManager& display;

	GLuint reflectionFrameBufferID;
	GLuint reflectionTextureID;
	GLuint reflectionDepthBufferID;
	
	GLuint refractionFrameBufferID;
	GLuint refractionTextureID;
	GLuint refractionDepthBufferID;
	GLuint refractionDepthTextureID;
	
	void initializeRefractionFrameBuffer();
	void initializeReflectionFrameBuffer();
	void bindFrameBuffer(GLuint framebufferID, GLsizei width, GLsizei height);
	GLuint createFrameBuffer();
	GLuint createTextureAttachment(GLsizei width, GLsizei height);
	GLuint createDepthTextureAttachment(GLsizei width, GLsizei height);
	GLuint createDepthBufferAttachment(GLsizei width, GLsizei height);
};

#endif
