#ifndef TERRAINSHADER_H
#define TERRAINSHADER_H

#include "ShaderProgram.h"
#include "Light.h"
#include "Camera.h"

class TerrainShader: public ShaderProgram
{
public:
	TerrainShader();
	void bindAttributes();
	void getAllUniformLocations();
	void connectTextureUnits();
	void loadShineVariables(GLfloat damper, GLfloat reflectivity);
	void loadTransformationMatrix(glm::mat4& matrix);
	void loadLights(vector<Light*>& lights);
	void loadProjectionMatrix(glm::mat4& matrix);
	void loadViewMatrix(Camera& camera);
	void loadSkyColor(GLfloat r, GLfloat g, GLfloat b);
	void loadFogVariables(GLfloat density, GLfloat gradient);
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
	int location_skyColor;
	int location_fogDensity;
	int location_fogGradient;
	int location_backgroundTexture;
	int location_rTexture;
	int location_gTexture;
	int location_bTexture;
	int location_blendMap;
	int location_clipPlane;
};

#endif
