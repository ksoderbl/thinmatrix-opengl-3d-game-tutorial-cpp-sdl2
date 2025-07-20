#include "TerrainShader.h"
#include "Maths.h"

const string VERTEX_FILE = "shaders/terrainVertexShader.glsl";
const string FRAGMENT_FILE = "shaders/terrainFragmentShader.glsl";

TerrainShader::TerrainShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE)
{
	bindAttributes();
	linkProgram();
	getAllUniformLocations();
}

void TerrainShader::bindAttributes()
{
	bindAttribute(0, "position");
	bindAttribute(1, "textureCoords");
	bindAttribute(2, "normal"); // "normal" variable in the vertex shader
}

void TerrainShader::loadTransformationMatrix(glm::mat4& matrix)
{
	loadMatrix(location_transformationMatrix, matrix);
}

void TerrainShader::loadLights(vector<Light*>& lights)
{
	for (int i = 0; i < MAX_LIGHTS; i++) {
		if (i < (int)lights.size()) {
			Light* light = lights[i];
			loadVector(location_lightPosition[i], light->getPosition());
			loadVector(location_lightColor[i], light->getColor());
		} else {
			// If less than MAX_LIGHTS lights are in the lights vector,
			// load up empty information to the shaders.
			glm::vec3 zero(0.0f, 0.0f, 0.0f);
			loadVector(location_lightPosition[i], zero);
			loadVector(location_lightColor[i], zero);
		}
	}
}

void TerrainShader::loadProjectionMatrix(glm::mat4& matrix)
{
	loadMatrix(location_projectionMatrix, matrix);
}

void TerrainShader::loadViewMatrix(Camera& camera)
{
	glm::mat4 viewMatrix = Maths::createViewMatrix(camera);
	loadMatrix(location_viewMatrix, viewMatrix);
}

void TerrainShader::getAllUniformLocations()
{
	location_transformationMatrix = getUniformLocation("transformationMatrix");
	location_projectionMatrix = getUniformLocation("projectionMatrix");
	location_viewMatrix = getUniformLocation("viewMatrix");
	location_shineDamper = getUniformLocation("shineDamper");
	location_reflectivity = getUniformLocation("reflectivity");
	location_skyColor = getUniformLocation("skyColor");
	location_backgroundTexture = getUniformLocation("backgroundTexture");
	location_rTexture = getUniformLocation("rTexture");
	location_gTexture = getUniformLocation("gTexture");
	location_bTexture = getUniformLocation("bTexture");
	location_blendMap = getUniformLocation("blendMap");

	for (int i = 0; i < MAX_LIGHTS; i++) {
		string iStr = std::to_string(i);
		location_lightPosition[i] = getUniformLocation("lightPosition[" + iStr + "]");
		location_lightColor[i] = getUniformLocation("lightColor[" + iStr + "]");
	}
}

void TerrainShader::connectTextureUnits()
{
	loadInt(location_backgroundTexture, 0);
	loadInt(location_rTexture, 1);
	loadInt(location_gTexture, 2);
	loadInt(location_bTexture, 3);
	loadInt(location_blendMap, 4);
}

void TerrainShader::loadShineVariables(GLfloat damper, GLfloat reflectivity)
{
	loadFloat(location_shineDamper, damper);
	loadFloat(location_reflectivity, reflectivity);
}

void TerrainShader::loadSkyColor(GLfloat r, GLfloat g, GLfloat b)
{
	glm::vec3 vec(r, g, b);
	loadVector(location_skyColor, vec);
}
