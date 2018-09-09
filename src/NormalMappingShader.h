#ifndef NORMALMAPPINGSHADER_H
#define NORMALMAPPINGSHADER_H

#include "ShaderProgram.h"
#include "Light.h"
#include "Camera.h"

class NormalMappingShader: public ShaderProgram
{
public:
	NormalMappingShader();
	void bindAttributes();
	void getAllUniformLocations();
	void connectTextureUnits();
	void loadShineVariables(GLfloat damper, GLfloat reflectivity);
	void loadTransformationMatrix(glm::mat4& matrix);
	void loadLights(vector<Light*>& lights);
	void loadProjectionMatrix(glm::mat4& matrix);
	void loadViewMatrix(Camera& camera);
	void loadFakeLightingVariable(bool useFakeLighting);
	void loadSkyColor(GLfloat r, GLfloat g, GLfloat b);
	void loadNumberOfRows(int numberOfRows);
	void loadTextureOffset(GLfloat x, GLfloat y);
	void loadClipPlane(glm::vec4& vec);
private:
	static constexpr int MAX_LIGHTS = 4;
	int location_transformationMatrix;
	int location_projectionMatrix;
	int location_viewMatrix;
	int location_lightPosition[MAX_LIGHTS];
	int location_lightColor[MAX_LIGHTS];
	int location_attenuation[MAX_LIGHTS];
	int location_shineDamper;
	int location_reflectivity;
	int location_useFakeLighting;
	int location_skyColor;
	int location_numberOfRows;
	int location_textureOffset;
	int location_clipPlane;
	int location_modelTexture;
	int location_normalMap;
};

#endif
