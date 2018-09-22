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
	location_skyColor = getUniformLocation("skyColor");
	location_cubeMap = getUniformLocation("cubeMap");
	location_cubeMap2 = getUniformLocation("cubeMap2");
	location_blendFactor = getUniformLocation("blendFactor");
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
	rotation += ROTATE_SPEED * display.getFrameTimeSeconds();
	viewMatrix = glm::rotate(viewMatrix, glm::radians(rotation), glm::vec3(0, 1, 0));
	loadMatrix(location_viewMatrix, viewMatrix);
}

void SkyboxShader::loadFogColor(GLfloat r, GLfloat g, GLfloat b)
{
	glm::vec3 vec(r, g, b);
	loadVector(location_skyColor, vec);
}

void SkyboxShader::connectTextureUnits()
{
	loadInt(location_cubeMap, 0);
	loadInt(location_cubeMap2, 1);
}

void SkyboxShader::loadBlendFactor(GLfloat blend)
{
	loadFloat(location_blendFactor, blend);
}
