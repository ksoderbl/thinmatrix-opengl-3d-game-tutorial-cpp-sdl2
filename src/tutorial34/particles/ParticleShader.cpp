#include "ParticleShader.h"
#include "../Maths.h"

const string VERTEX_FILE = "particles/particleVShader.glsl";
const string FRAGMENT_FILE = "particles/particleFShader.glsl";

ParticleShader::ParticleShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE)
{
	bindAttributes();
	linkProgram();
	getAllUniformLocations();
}

void ParticleShader::bindAttributes()
{
	bindAttribute(0, "position");
}

void ParticleShader::loadModelViewMatrix(glm::mat4& matrix)
{
	loadMatrix(location_modelViewMatrix, matrix);
}

void ParticleShader::loadProjectionMatrix(glm::mat4& matrix)
{
	loadMatrix(location_projectionMatrix, matrix);
}

void ParticleShader::getAllUniformLocations()
{
	location_modelViewMatrix = getUniformLocation("modelViewMatrix");
	location_projectionMatrix = getUniformLocation("projectionMatrix");
}
