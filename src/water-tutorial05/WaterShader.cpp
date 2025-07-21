#include "WaterShader.h"
#include "Maths.h"

const string VERTEX_FILE = "water/waterVertex.glsl";
const string FRAGMENT_FILE = "water/waterFragment.glsl";

WaterShader::WaterShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE)
{
	bindAttributes();
	linkProgram();
	getAllUniformLocations();
}

void WaterShader::bindAttributes()
{
	bindAttribute(0, "position");
}

void WaterShader::loadMoveFactor(GLfloat factor)
{
	loadFloat(location_moveFactor, factor);
}

void WaterShader::loadProjectionMatrix(glm::mat4& matrix)
{
	loadMatrix(location_projectionMatrix, matrix);
}

void WaterShader::loadViewMatrix(Camera& camera)
{
	glm::mat4 viewMatrix = Maths::createViewMatrix(camera);
	loadMatrix(location_viewMatrix, viewMatrix);
}

void WaterShader::loadModelMatrix(glm::mat4& matrix)
{
	loadMatrix(location_modelMatrix, matrix);
}

void WaterShader::getAllUniformLocations()
{
	location_projectionMatrix = getUniformLocation("projectionMatrix");
	location_viewMatrix = getUniformLocation("viewMatrix");
	location_modelMatrix = getUniformLocation("modelMatrix");
	location_reflectionTexture = getUniformLocation("reflectionTexture");
	location_refractionTexture = getUniformLocation("refractionTexture");
	location_dudvMap = getUniformLocation("dudvMap");
	location_moveFactor = getUniformLocation("moveFactor");
}

void WaterShader::connectTextureUnits()
{
	loadInt(location_reflectionTexture, 0);
	loadInt(location_refractionTexture, 1);
	loadInt(location_dudvMap, 2);
}
