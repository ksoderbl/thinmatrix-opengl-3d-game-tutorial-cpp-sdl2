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
	
protected:
	static constexpr GLsizei REFLECTION_WIDTH = 320*2;
	static constexpr GLsizei REFLECTION_HEIGHT = 180*2;
	static constexpr GLsizei REFRACTION_WIDTH = 320*2;
	static constexpr GLsizei REFRACTION_HEIGHT = 180*2;
	
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
