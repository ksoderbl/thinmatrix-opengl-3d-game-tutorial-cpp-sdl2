#include "StaticShader.h"
#include "Maths.h"

const string VERTEX_FILE = "shaders/vertexShader.glsl";
const string FRAGMENT_FILE = "shaders/fragmentShader.glsl";

StaticShader::StaticShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE)
{
	bindAttributes();
	linkProgram();
	getAllUniformLocations();
}

void StaticShader::bindAttributes()
{
	bindAttribute(0, "position");
	bindAttribute(1, "textureCoords");
	bindAttribute(2, "normal"); // "normal" variable in the vertex shader
}

void StaticShader::getAllUniformLocations()
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

	for (int i = 0; i < MAX_LIGHTS; i++) {
		string iStr = std::to_string(i);
		location_lightPosition[i] = getUniformLocation("lightPosition[" + iStr + "]");
		location_lightColor[i] = getUniformLocation("lightColor[" + iStr + "]");
	}
}

void StaticShader::loadTransformationMatrix(glm::mat4& matrix)
{
	loadMatrix(location_transformationMatrix, matrix);
}

void StaticShader::loadLights(vector<Light*>& lights)
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

void StaticShader::loadProjectionMatrix(glm::mat4& matrix)
{
	loadMatrix(location_projectionMatrix, matrix);
}

void StaticShader::loadViewMatrix(Camera& camera)
{
	glm::mat4 viewMatrix = Maths::createViewMatrix(camera);
	loadMatrix(location_viewMatrix, viewMatrix);
}

void StaticShader::loadFakeLightingVariable(bool useFakeLighting)
{
	loadBoolean(location_useFakeLighting, useFakeLighting);
}

void StaticShader::loadShineVariables(GLfloat damper, GLfloat reflectivity)
{
	loadFloat(location_shineDamper, damper);
	loadFloat(location_reflectivity, reflectivity);
}

void StaticShader::loadSkyColor(GLfloat r, GLfloat g, GLfloat b)
{
	glm::vec3 vec(r, g, b);
	loadVector(location_skyColor, vec);
}

void StaticShader::loadNumberOfRows(int numberOfRows)
{
	loadFloat(location_numberOfRows, (GLfloat)numberOfRows);
}

void StaticShader::loadTextureOffset(GLfloat x, GLfloat y)
{
	glm::vec2 vec(x, y);
	load2DVector(location_textureOffset, vec);
}

void StaticShader::loadClipPlane(glm::vec4& vec)
{
	loadVector(location_clipPlane, vec);
}
