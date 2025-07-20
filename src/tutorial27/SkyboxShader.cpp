#include "SkyboxShader.h"
#include "Maths.h"

const string VERTEX_FILE = "skybox/skyboxVertexShader.glsl";
const string FRAGMENT_FILE = "skybox/skyboxFragmentShader.glsl";

SkyboxShader::SkyboxShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE)
{
	bindAttributes();
	linkProgram();
	getAllUniformLocations();
}

void SkyboxShader::bindAttributes()
{
	bindAttribute(0, "position");
}

void SkyboxShader::getAllUniformLocations()
{
	location_projectionMatrix = getUniformLocation("projectionMatrix");
	location_viewMatrix = getUniformLocation("viewMatrix");
}

void SkyboxShader::loadProjectionMatrix(glm::mat4& matrix)
{
	loadMatrix(location_projectionMatrix, matrix);
}

void SkyboxShader::loadViewMatrix(Camera& camera)
{
	glm::mat4 viewMatrix = Maths::createViewMatrix(camera);
	// set translations to 0 in view matrix
	viewMatrix[3][0] = 0.0f;
	viewMatrix[3][1] = 0.0f;
	viewMatrix[3][2] = 0.0f;
	loadMatrix(location_viewMatrix, viewMatrix);
}
