#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "Headers.h"
#include "Camera.h"
#include "Maths.h"
#include "Light.h"

class ShaderProgram
{
public:
	ShaderProgram(string vertexFile, string fragmentFile);
	void linkProgram();
	int getShaderProgram() { return programID; }
	void start();
	void stop();
	void cleanUp();
	void bindAttribute(int attribute, string variableName);
	int getUniformLocation(string uniformName);

	void loadInt(int location, GLint value);
	void loadFloat(int location, GLfloat value);
	void loadVector(int location, glm::vec3& vec);
	void load2DVector(int location, glm::vec2& vec);
	void loadBoolean(int location, bool value);
	void loadMatrix(int location, glm::mat4& matrix);

private:
	int loadShader(string fileName, GLenum type);
	string readShaderSource(string fileName);

	string vertexFile;
	string fragmentFile;
	int programID;
	int vertexShaderID;
	int fragmentShaderID;
};

#endif
