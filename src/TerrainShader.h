
#ifndef TERRAINSHADER_H
#define TERRAINSHADER_H

#include "ShaderProgram.h"

class TerrainShader: public ShaderProgram
{
public:
	TerrainShader();
	void bindAttributes();
	void getAllUniformLocations();
	void connectTextureUnits();
	void loadShineVariables(GLfloat damper, GLfloat reflectivity);
	void loadTransformationMatrix(glm::mat4& matrix);
	void loadLight(Light& light);
	void loadProjectionMatrix(glm::mat4& matrix);
	void loadViewMatrix(Camera& camera);
	void loadSkyColor(GLfloat r, GLfloat g, GLfloat b);

private:
	int location_transformationMatrix;
	int location_projectionMatrix;
	int location_viewMatrix;
	int location_lightPosition;
	int location_lightColor;
	int location_shineDamper;
	int location_reflectivity;
	int location_skyColor;
	int location_backgroundTexture;
	int location_rTexture;
	int location_gTexture;
	int location_bTexture;
	int location_blendMap;
};

#endif
