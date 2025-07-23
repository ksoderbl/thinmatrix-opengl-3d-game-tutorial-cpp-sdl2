
#include "TerrainShader.h"

const string VERTEX_FILE = "shaders/terrainVertexShader.glsl";
const string FRAGMENT_FILE = "shaders/terrainFragmentShader.glsl";

TerrainShader::TerrainShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE)
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
		cerr << "Could not link shader program" << endl;
		exit(1);
	}
	getAllUniformLocations();
}

int TerrainShader::getUniformLocation(string uniformName)
{
	return glGetUniformLocation(programID, uniformName.c_str());
}

void TerrainShader::start()
{
	glUseProgram(programID);
}

void TerrainShader::stop()
{
	glUseProgram(0);
}

void TerrainShader::cleanUp()
{
	stop();
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteProgram(vertexShaderID);
	glDeleteProgram(fragmentShaderID);
	glDeleteProgram(programID);
}

void TerrainShader::bindAttribute(int attribute, string variableName)
{
	glBindAttribLocation(programID, attribute, variableName.c_str());
}

// should be virtual
void TerrainShader::bindAttributes()
{
	bindAttribute(0, "position");
	bindAttribute(1, "textureCoords");
	bindAttribute(2, "normal"); // "normal" variable in the vertex shader
}

/*
void TerrainShader::loadFloat(int location, GLfloat value)
{
	glUniform1f(location, value);
}

void TerrainShader::loadVector(int location, glm::vec3& vec)
{
	glUniform3f(location, vec[0], vec[1], vec[2]);
}

void TerrainShader::loadBoolean(int location, bool value)
{
	GLfloat toLoad = (value ? 1 : 0);
	glUniform1f(location, toLoad);
}

// value needs to have 16 components for a 4 x 4 matrix
void TerrainShader::loadMatrix(int location, glm::mat4& matrix)
{
	glUniformMatrix4fv(location, 1, false, &matrix[0][0]);
}
*/

void TerrainShader::loadTransformationMatrix(glm::mat4& matrix)
{
	loadMatrix(location_transformationMatrix, matrix);
}

void TerrainShader::loadLight(Light& light)
{
	loadVector(location_lightPosition, light.getPosition());
	loadVector(location_lightColor, light.getColor());
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
	location_lightPosition = getUniformLocation("lightPosition");
	location_lightColor = getUniformLocation("lightColor");
	location_shineDamper = getUniformLocation("shineDamper");
	location_reflectivity = getUniformLocation("reflectivity");
	location_skyColor = getUniformLocation("skyColor");
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
