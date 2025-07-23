#ifndef SKYBOXSHADER_H
#define SKYBOXSHADER_H

#include "ShaderProgram.h"
#include "Camera.h"

class SkyboxShader: public ShaderProgram
{
public:
	SkyboxShader();
	void bindAttributes();
	void getAllUniformLocations();
	void loadProjectionMatrix(glm::mat4& matrix);
	void loadViewMatrix(Camera& camera, DisplayManager& display);
	void loadFogColor(GLfloat r, GLfloat g, GLfloat b);
	void loadBlendFactor(GLfloat blend);
	void connectTextureUnits();

	static constexpr GLfloat ROTATE_SPEED = 0.1f;
private:
	int location_projectionMatrix;
	int location_viewMatrix;
	int location_skyColor;
	int location_cubeMap;
	int location_cubeMap2;
	int location_blendFactor;
	GLfloat rotation = 0;
};

#endif
