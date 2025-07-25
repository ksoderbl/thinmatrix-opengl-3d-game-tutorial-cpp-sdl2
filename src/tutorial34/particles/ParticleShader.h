#ifndef PARTICLESHADER_H
#define PARTICLESHADER_H

#include "../ShaderProgram.h"
#include "../Light.h"
#include "../Camera.h"

class ParticleShader: public ShaderProgram
{
public:
	ParticleShader();
	void getAllUniformLocations();
	void bindAttributes();
	void loadModelViewMatrix(glm::mat4& matrix);
	void loadProjectionMatrix(glm::mat4& matrix);
private:
	int location_modelViewMatrix;
	int location_projectionMatrix;
};

#endif
