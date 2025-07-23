#ifndef WATERRENDERER_H
#define WATERRENDERER_H

#include "Headers.h"
#include "Loader.h"
#include "WaterShader.h"
#include "WaterTile.h"
#include "WaterFrameBuffers.h"
#include "Camera.h"
#include "RawModel.h"
#include "DisplayManager.h"

class WaterRenderer {
public:
	WaterRenderer(Loader& loader, WaterShader& shader, glm::mat4& projectionMatrix, WaterFrameBuffers& fbos);
	void render(vector<WaterTile*>& water, Camera& camera, DisplayManager& display);
	void prepareRender(Camera& camera, DisplayManager& display);
	void unbind();
	void setUpVAO(Loader& loader);
private:
	RawModel* quad;
	WaterShader& shader;
	WaterFrameBuffers& fbos;
	GLuint dudvTexture;
	const string DUDV_MAP = "waterDUDV6";
	static constexpr GLfloat WAVE_SPEED = 0.02f;
	GLfloat moveFactor = 0;
};

#endif
