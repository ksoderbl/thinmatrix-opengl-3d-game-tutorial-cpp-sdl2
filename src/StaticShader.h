
#ifndef STATICSHADER_H
#define STATICSHADER_H

#include "ShaderProgram.h"

class StaticShader: public ShaderProgram
{
public:
	StaticShader();
	void start();
	void stop();
	void cleanUp();
	void bindAttribute(int attribute, string variableName);
	void bindAttributes();
	int getShaderProgram() { return programID; }
	int getUniformLocation(string uniformName);
	void getAllUniformLocations();
	void loadShineVariables(GLfloat damper, GLfloat reflectivity);
	void loadTransformationMatrix(glm::mat4& matrix);
	void loadLight(Light& light);
	void loadProjectionMatrix(glm::mat4& matrix);
	void loadViewMatrix(Camera& camera);
	void loadFakeLightingVariable(bool useFakeLighting);
	void loadSkyColor(GLfloat r, GLfloat g, GLfloat b);

private:
	int programID;
	int vertexShaderID;
	int fragmentShaderID;

	int location_transformationMatrix;
	int location_projectionMatrix;
	int location_viewMatrix;
	int location_lightPosition;
	int location_lightColor;
	int location_shineDamper;
	int location_reflectivity;
	int location_useFakeLighting;
	int location_skyColor;
};

#endif
