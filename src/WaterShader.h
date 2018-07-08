#ifndef WATERSHADER_H
#define WATERSHADER_H

#include "ShaderProgram.h"
#include "Light.h"
#include "Camera.h"

class WaterShader: public ShaderProgram
{
public:
	WaterShader();
	void bindAttributes();
	void getAllUniformLocations();
	void loadProjectionMatrix(glm::mat4& matrix);
	void loadViewMatrix(Camera& camera);
	void loadModelMatrix(glm::mat4& matrix);
private:
	int location_modelMatrix;
	int location_viewMatrix;
	int location_projectionMatrix;
};

#endif
