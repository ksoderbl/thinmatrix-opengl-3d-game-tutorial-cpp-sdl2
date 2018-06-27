
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
	void loadInt(int location, GLint value);
	void loadFloat(int location, GLfloat value);
	void loadVector(int location, glm::vec3& vec);
	void loadBoolean(int location, bool value);
	void loadMatrix(int location, glm::mat4& matrix);

	int loadShader(string fileName, GLenum type);
	string readShaderSource(string fileName);
};

#endif
