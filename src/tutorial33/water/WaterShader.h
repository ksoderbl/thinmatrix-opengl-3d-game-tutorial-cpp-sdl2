#ifndef WATERSHADER_H
#define WATERSHADER_H

#include "../ShaderProgram.h"
#include "../Camera.h"
#include "../Light.h"

class WaterShader: public ShaderProgram
{
public:
	WaterShader();
	void bindAttributes();
	void connectTextureUnits();
	void loadShineVariables(GLfloat shineDamper, GLfloat reflectivity);
	void loadLight(Light& sun);
	void loadNearPlane(GLfloat nearPlane);
	void loadFarPlane(GLfloat farPlane);
	void loadWaterReflectivity(GLfloat reflectivity);
	void loadWaterTiling(GLfloat factor);
	void loadMoveFactor(GLfloat factor);
	void loadWaveStrength(GLfloat factor);
	void loadSkyColor(GLfloat r, GLfloat g, GLfloat b);
	void loadProjectionMatrix(glm::mat4& matrix);
	void loadViewMatrix(Camera& camera);
	void loadModelMatrix(glm::mat4& matrix);
	void getAllUniformLocations();
private:
	int location_modelMatrix;
	int location_viewMatrix;
	int location_projectionMatrix;
	int location_waterTiling;
	int location_reflectionTexture;
	int location_refractionTexture;
	int location_dudvMap;
	int location_waveStrength;
	int location_moveFactor;
	int location_cameraPosition;
	int location_waterReflectivity;
	int location_normalMap;
	int location_lightColor;
	int location_lightPosition;
	int location_shineDamper;
	int location_reflectivity;
	int location_depthMap;
	int location_nearPlane;
	int location_farPlane;
	int location_skyColor;
};

#endif
