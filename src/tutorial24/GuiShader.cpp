#include "GuiShader.h"

const string VERTEX_FILE = "guis/guiVertexShader.glsl";
const string FRAGMENT_FILE = "guis/guiFragmentShader.glsl";

GuiShader::GuiShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE)
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

int GuiShader::getUniformLocation(string uniformName)
{
	return glGetUniformLocation(programID, uniformName.c_str());
}

void GuiShader::start()
{
	glUseProgram(programID);
}

void GuiShader::stop()
{
	glUseProgram(0);
}

void GuiShader::cleanUp()
{
	stop();
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteProgram(vertexShaderID);
	glDeleteProgram(fragmentShaderID);
	glDeleteProgram(programID);
}

void GuiShader::bindAttribute(int attribute, string variableName)
{
	glBindAttribLocation(programID, attribute, variableName.c_str());
}

void GuiShader::bindAttributes()
{
	bindAttribute(0, "position");
}

void GuiShader::loadTransformationMatrix(glm::mat4& matrix)
{
	loadMatrix(location_transformationMatrix, matrix);
}

void GuiShader::getAllUniformLocations()
{
	location_transformationMatrix = getUniformLocation("transformationMatrix");
}

