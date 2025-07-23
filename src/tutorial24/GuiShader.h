#ifndef GUISHADER_H
#define GUISHADER_H

#include "ShaderProgram.h"

class GuiShader: public ShaderProgram
{
public:
	GuiShader();
	void start();
	void stop();
	void cleanUp();
	void bindAttribute(int attribute, string variableName);
	void bindAttributes();
	int getShaderProgram() { return programID; }
	int getUniformLocation(string uniformName);
	void getAllUniformLocations();
	void connectTextureUnits();
	void loadTransformationMatrix(glm::mat4& matrix);

private:
	int programID;
	int vertexShaderID;
	int fragmentShaderID;

	int location_transformationMatrix;
};

#endif
