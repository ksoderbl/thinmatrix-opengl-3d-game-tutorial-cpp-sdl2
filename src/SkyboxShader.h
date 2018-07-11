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
	void loadViewMatrix(Camera& camera);
private:
	int location_projectionMatrix;
	int location_viewMatrix;
};

#endif
