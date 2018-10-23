#ifndef PARTICLESHADER_H
#define PARTICLESHADER_H

#include "../shaders/ShaderProgram.h"
#include "../entities/Light.h"
#include "../entities/Camera.h"

class ParticleShader: public ShaderProgram
{
public:
	ParticleShader();
	void getAllUniformLocations();
	void bindAttributes();
	void loadModelViewMatrix(glm::mat4& matrix);
	void loadProjectionMatrix(glm::mat4& matrix);
	void loadNumberOfRows(GLfloat numRows);
private:
	int location_projectionMatrix;
	int location_numberOfRows;
};

#endif
