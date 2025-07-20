#include "NormalMappingShader.h"
#include "Maths.h"

const string VERTEX_FILE = "normalMappingRenderer/normalMapVShader.glsl";
const string FRAGMENT_FILE = "normalMappingRenderer/normalMapFShader.glsl";

NormalMappingShader::NormalMappingShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE)
{
	bindAttributes();
	linkProgram();
	getAllUniformLocations();
}

void NormalMappingShader::bindAttributes()
{
	bindAttribute(0, "position");
	bindAttribute(1, "textureCoords");
	bindAttribute(2, "normal");
	bindAttribute(3, "tangent");
}

void NormalMappingShader::getAllUniformLocations()
{
	location_transformationMatrix = getUniformLocation("transformationMatrix");
	location_projectionMatrix = getUniformLocation("projectionMatrix");
	location_viewMatrix = getUniformLocation("viewMatrix");
	location_shineDamper = getUniformLocation("shineDamper");
	location_reflectivity = getUniformLocation("reflectivity");
	location_useFakeLighting = getUniformLocation("useFakeLighting");
	location_skyColor = getUniformLocation("skyColor");
	location_numberOfRows = getUniformLocation("numberOfRows");
	location_textureOffset = getUniformLocation("textureOffset");
	location_clipPlane = getUniformLocation("clipPlane");
	location_modelTexture = getUniformLocation("modelTexture");
	location_normalMap = getUniformLocation("normalMap");

	for (int i = 0; i < MAX_LIGHTS; i++) {
		string iStr = std::to_string(i);
		location_lightPosition[i] = getUniformLocation("lightPosition[" + iStr + "]");
		location_lightColor[i] = getUniformLocation("lightColor[" + iStr + "]");
		location_attenuation[i] = getUniformLocation("attenuation[" + iStr + "]");
	}
}

void NormalMappingShader::connectTextureUnits()
{
	loadInt(location_modelTexture, 0);
	loadInt(location_normalMap, 1);
}

void NormalMappingShader::loadTransformationMatrix(glm::mat4& matrix)
{
	loadMatrix(location_transformationMatrix, matrix);
}

void NormalMappingShader::loadLights(vector<Light*>& lights)
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

void NormalMappingShader::loadProjectionMatrix(glm::mat4& matrix)
{
	loadMatrix(location_projectionMatrix, matrix);
}

void NormalMappingShader::loadViewMatrix(Camera& camera)
{
	glm::mat4 viewMatrix = Maths::createViewMatrix(camera);
	loadMatrix(location_viewMatrix, viewMatrix);
}

void NormalMappingShader::loadFakeLightingVariable(bool useFakeLighting)
{
	loadBoolean(location_useFakeLighting, useFakeLighting);
}

void NormalMappingShader::loadShineVariables(GLfloat damper, GLfloat reflectivity)
{
	loadFloat(location_shineDamper, damper);
	loadFloat(location_reflectivity, reflectivity);
}

void NormalMappingShader::loadSkyColor(GLfloat r, GLfloat g, GLfloat b)
{
	glm::vec3 vec(r, g, b);
	loadVector(location_skyColor, vec);
}

void NormalMappingShader::loadNumberOfRows(int numberOfRows)
{
	loadFloat(location_numberOfRows, (GLfloat)numberOfRows);
}

void NormalMappingShader::loadTextureOffset(GLfloat x, GLfloat y)
{
	glm::vec2 vec(x, y);
	load2DVector(location_textureOffset, vec);
}

void NormalMappingShader::loadClipPlane(glm::vec4& vec)
{
	loadVector(location_clipPlane, vec);
}
