#include "ParticleShader.h"
#include "../toolbox/Maths.h"

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

void ParticleShader::loadTextureCoordInfo(
	glm::vec2& offset1, glm::vec2& offset2,
	GLfloat numRows, GLfloat blend)
{
	load2DVector(location_texOffset1, offset1);
	load2DVector(location_texOffset2, offset2);
	glm::vec2 vec = glm::vec2(numRows, blend);
	load2DVector(location_texCoordInfo, vec);
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
	location_texOffset1 = getUniformLocation("texOffset1");
	location_texOffset2 = getUniformLocation("texOffset2");
	location_texCoordInfo = getUniformLocation("texCoordInfo");
}
