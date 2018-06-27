
#include "StaticShader.h"

const string VERTEX_FILE = "shaders/vertexShader.glsl";
const string FRAGMENT_FILE = "shaders/fragmentShader.glsl";

StaticShader::StaticShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE)
{
	string vertexFile = VERTEX_FILE;
	string fragmentFile = FRAGMENT_FILE;
	vertexShaderID = loadShader(vertexFile, GL_VERTEX_SHADER);
	fragmentShaderID = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	bindAttributes();
	glLinkProgram(programID);
	glValidateProgram(programID);
	GLint status;
	glGetProgramiv(programID, GL_LINK_STATUS, &status);
	if (status != GL_TRUE) {
		GLchar infoLog[1024];
		GLsizei length;
		glGetShaderInfoLog(programID, sizeof(infoLog), &length, infoLog);
		string s(infoLog);
		cerr << s << endl;
		cerr << "Vertex shader: " << vertexFile << endl;
		cerr << "Fragment shader: " << fragmentFile << endl;
		cerr << "Could not link shader program" << endl;
		exit(1);
	}
	getAllUniformLocations();
}

int StaticShader::getUniformLocation(string uniformName)
{
	return glGetUniformLocation(programID, uniformName.c_str());
}

void StaticShader::start()
{
	glUseProgram(programID);
}

void StaticShader::stop()
{
	glUseProgram(0);
}

void StaticShader::cleanUp()
{
	stop();
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteProgram(vertexShaderID);
	glDeleteProgram(fragmentShaderID);
	glDeleteProgram(programID);
}

void StaticShader::bindAttribute(int attribute, string variableName)
{
	glBindAttribLocation(programID, attribute, variableName.c_str());
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
	location_lightPosition = getUniformLocation("lightPosition");
	location_lightColor = getUniformLocation("lightColor");
	location_shineDamper = getUniformLocation("shineDamper");
	location_reflectivity = getUniformLocation("reflectivity");
	location_useFakeLighting = getUniformLocation("useFakeLighting");
	location_skyColor = getUniformLocation("skyColor");
}

void StaticShader::loadTransformationMatrix(glm::mat4& matrix)
{
	loadMatrix(location_transformationMatrix, matrix);
}

void StaticShader::loadLight(Light& light)
{
	loadVector(location_lightPosition, light.getPosition());
	loadVector(location_lightColor, light.getColor());
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
