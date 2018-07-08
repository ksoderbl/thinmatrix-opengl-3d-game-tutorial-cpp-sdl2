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
	static constexpr GLint REFLECTION_WIDTH = 320;
	static constexpr GLint REFLECTION_HEIGHT = 180;
	static constexpr GLint REFRACTION_WIDTH = 1280;
	static constexpr GLint REFRACTION_HEIGHT = 720;
	
private:
	DisplayManager& display;

	GLuint reflectionFrameBufferID;
	GLuint reflectionTextureID;
	GLuint reflectionDepthBufferID;
	
	GLuint refractionFrameBufferID;
	GLuint refractionTextureID;
	GLuint refractionDepthTextureID;
	
	void initializeRefractionFrameBuffer();
	void initializeReflectionFrameBuffer();
	void bindFrameBuffer(GLuint framebufferID, GLint width, GLint height);
	GLuint createFrameBuffer();
	GLuint createTextureAttachment(GLint width, GLint GLheight);
	GLuint createDepthTextureAttachment(GLint width, GLint GLheight);
	GLuint createDepthBufferAttachment(GLint width, GLint GLheight);
};

#endif
