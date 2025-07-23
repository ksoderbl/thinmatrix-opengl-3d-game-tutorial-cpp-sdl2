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
	void loadTextureCoordInfo(glm::vec2& offset1, glm::vec2& offset2, GLfloat numRows, GLfloat blend);
private:
	int location_modelViewMatrix;
	int location_projectionMatrix;
	int location_texOffset1;
	int location_texOffset2;
	int location_texCoordInfo;
};

#endif
