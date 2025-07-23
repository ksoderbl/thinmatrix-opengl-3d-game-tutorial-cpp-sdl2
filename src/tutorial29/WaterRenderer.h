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
#include "Light.h"

class WaterRenderer {
public:
	WaterRenderer(
		Loader& loader,
		WaterShader& shader,
		glm::mat4& projectionMatrix,
		GLfloat nearPlane,
		GLfloat farPlane,
		WaterFrameBuffers& fbos);
	void render(
		vector<WaterTile*>& water,
		Camera& camera,
		Light& sun,
		DisplayManager& display);
	void prepareRender(
		Camera& camera,
		Light& sun,
		DisplayManager& display);
	void unbind();
	void setUpVAO(Loader& loader);
private:
	RawModel* quad;
	WaterShader& shader;
	WaterFrameBuffers& fbos;
	GLuint dudvTexture;
	GLuint normalMap;
	const string DUDV_MAP = "waterDUDV6";
	const string NORMAL_MAP = "normalMap7";
	static constexpr GLfloat WAVE_SPEED = 0.03f;
	GLfloat waterTiling;
	GLfloat moveFactor;
	GLfloat waveStrength;
	GLfloat waterReflectivity;
	GLfloat shineDamper;
	GLfloat reflectivity;
};

#endif
