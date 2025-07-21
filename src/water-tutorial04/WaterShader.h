#ifndef WATERSHADER_H
#define WATERSHADER_H

#include "ShaderProgram.h"
#include "Camera.h"

class WaterShader: public ShaderProgram
{
public:
	WaterShader();
	void bindAttributes();
	void getAllUniformLocations();
	void connectTextureUnits();
	void loadProjectionMatrix(glm::mat4& matrix);
	void loadViewMatrix(Camera& camera);
	void loadModelMatrix(glm::mat4& matrix);
private:
	int location_modelMatrix;
	int location_viewMatrix;
	int location_projectionMatrix;
	int location_reflectionTexture;
	int location_refractionTexture;
};

#endif
