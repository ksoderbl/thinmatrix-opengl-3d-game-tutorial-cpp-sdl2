#ifndef WATERSHADER_H
#define WATERSHADER_H

#include "ShaderProgram.h"
#include "Camera.h"
#include "Light.h"

class WaterShader: public ShaderProgram
{
public:
	WaterShader();
	void bindAttributes();
	void getAllUniformLocations();
	void connectTextureUnits();
	void loadMoveFactor(GLfloat factor);
	void loadProjectionMatrix(glm::mat4& matrix);
	void loadViewMatrix(Camera& camera);
	void loadModelMatrix(glm::mat4& matrix);
	void loadSkyColor(GLfloat r, GLfloat g, GLfloat b);
	void loadLight(Light& sun);
private:
	int location_modelMatrix;
	int location_viewMatrix;
	int location_projectionMatrix;
	int location_reflectionTexture;
	int location_refractionTexture;
	int location_dudvMap;
	int location_moveFactor;
	int location_cameraPosition;
	int location_skyColor;
	int location_normalMap;
	int location_lightColor;
	int location_lightPosition;
};

#endif
