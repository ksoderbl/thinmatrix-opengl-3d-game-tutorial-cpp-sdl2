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


void WaterShader::connectTextureUnits()
{
	loadInt(location_reflectionTexture, 0);
	loadInt(location_refractionTexture, 1);
	loadInt(location_dudvMap, 2);
	loadInt(location_normalMap, 3);
	loadInt(location_depthMap, 4);
}

void WaterShader::loadShineVariables(GLfloat shineDamper, GLfloat reflectivity)
{
	loadFloat(location_shineDamper, shineDamper);
	loadFloat(location_reflectivity, reflectivity);
}

// TODO: multiple lights
void WaterShader::loadLight(Light& sun)
{
	loadVector(location_lightColor, sun.getColor());
	loadVector(location_lightPosition, sun.getPosition());
}

void WaterShader::loadNearPlane(GLfloat nearPlane)
{
	loadFloat(location_nearPlane, nearPlane);
}

void WaterShader::loadFarPlane(GLfloat farPlane)
{
	loadFloat(location_farPlane, farPlane);
}

// 10.0: very reflective, 0.5: quite transparent
void WaterShader::loadWaterReflectivity(GLfloat reflectivity)
{
	loadFloat(location_waterReflectivity, reflectivity);
}

void WaterShader::loadWaterTiling(GLfloat factor)
{
	loadFloat(location_waterTiling, factor);
}

void WaterShader::loadMoveFactor(GLfloat factor)
{
	loadFloat(location_moveFactor, factor);
}


void WaterShader::loadWaveStrength(GLfloat factor)
{
	loadFloat(location_waveStrength, factor);
}


void WaterShader::loadSkyColor(GLfloat r, GLfloat g, GLfloat b)
{
	glm::vec3 vec(r, g, b);
	loadVector(location_skyColor, vec);
}

void WaterShader::loadProjectionMatrix(glm::mat4& matrix)
{
	loadMatrix(location_projectionMatrix, matrix);
}

void WaterShader::loadViewMatrix(Camera& camera)
{
	glm::mat4 viewMatrix = Maths::createViewMatrix(camera);
	loadMatrix(location_viewMatrix, viewMatrix);
	loadVector(location_cameraPosition, camera.getPosition());
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
	location_waterTiling = getUniformLocation("waterTiling");
	location_reflectionTexture = getUniformLocation("reflectionTexture");
	location_refractionTexture = getUniformLocation("refractionTexture");
	location_dudvMap = getUniformLocation("dudvMap");
	location_waveStrength = getUniformLocation("waveStrength");
	location_moveFactor = getUniformLocation("moveFactor");
	location_cameraPosition = getUniformLocation("cameraPosition");
	location_waterReflectivity = getUniformLocation("waterReflectivity");
	location_normalMap = getUniformLocation("normalMap");
	location_lightColor = getUniformLocation("lightColor");
	location_lightPosition = getUniformLocation("lightPosition");
	location_shineDamper = getUniformLocation("shineDamper");
	location_reflectivity = getUniformLocation("reflectivity");
	location_depthMap = getUniformLocation("depthMap");
	location_nearPlane = getUniformLocation("nearPlane");
	location_farPlane = getUniformLocation("farPlane");
	location_skyColor = getUniformLocation("skyColor");
}
