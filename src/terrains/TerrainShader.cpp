#include "TerrainShader.h"
#include "../toolbox/Maths.h"

const string VERTEX_FILE = "terrains/terrainVertexShader.glsl";
const string FRAGMENT_FILE = "terrains/terrainFragmentShader.glsl";

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
			loadVector(location_attenuation[i], light->getAttenuation());
		} else {
			// If less than MAX_LIGHTS lights are in the lights vector,
			// load up empty information to the shaders.
			glm::vec3 zero(0.0f, 0.0f, 0.0f);
			glm::vec3 unit(1.0f, 0.0f, 0.0f);
			loadVector(location_lightPosition[i], zero);
			loadVector(location_lightColor[i], zero);
			loadVector(location_attenuation[i], unit);
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
	location_fogDensity = getUniformLocation("fogDensity");
	location_fogGradient = getUniformLocation("fogGradient");
	location_backgroundTexture = getUniformLocation("backgroundTexture");
	location_rTexture = getUniformLocation("rTexture");
	location_gTexture = getUniformLocation("gTexture");
	location_bTexture = getUniformLocation("bTexture");
	location_blendMap = getUniformLocation("blendMap");
	location_clipPlane = getUniformLocation("clipPlane");

	for (int i = 0; i < MAX_LIGHTS; i++) {
		string iStr = std::to_string(i);
		location_lightPosition[i] = getUniformLocation("lightPosition[" + iStr + "]");
		location_lightColor[i] = getUniformLocation("lightColor[" + iStr + "]");
		location_attenuation[i] = getUniformLocation("attenuation[" + iStr + "]");
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

void TerrainShader::loadFogVariables(GLfloat density, GLfloat gradient)
{
	loadFloat(location_fogDensity, density);
	loadFloat(location_fogGradient, gradient);
}

void TerrainShader::loadClipPlane(glm::vec4& vec)
{
	loadVector(location_clipPlane, vec);
}
