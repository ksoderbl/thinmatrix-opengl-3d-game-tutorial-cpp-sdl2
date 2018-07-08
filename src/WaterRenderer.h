#ifndef WATERRENDERER_H
#define WATERRENDERER_H

#include "Headers.h"
#include "Loader.h"
#include "WaterShader.h"
#include "WaterTile.h"
#include "Camera.h"
#include "RawModel.h"

class WaterRenderer {
public:
	WaterRenderer(Loader& loader, WaterShader& shader, glm::mat4& projectionMatrix);
	void render(vector<WaterTile*>& water, Camera& camera);
	void prepareRender(Camera& camera);
	void unbind();
	void setUpVAO(Loader& loader);
private:
	RawModel* quad;
	WaterShader& shader;
};

#endif
