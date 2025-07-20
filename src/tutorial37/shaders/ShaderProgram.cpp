
#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(string vertexFile, string fragmentFile)
{
	this->vertexFile = SRC_LOC + vertexFile;
	this->fragmentFile = SRC_LOC + fragmentFile;
	vertexShaderID = loadShader(this->vertexFile, GL_VERTEX_SHADER);
	fragmentShaderID = loadShader(this->fragmentFile, GL_FRAGMENT_SHADER);
	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
}

void ShaderProgram::linkProgram()
{
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
}

void ShaderProgram::start()
{
	glUseProgram(programID);
}

void ShaderProgram::stop()
{
	glUseProgram(0);
}

void ShaderProgram::cleanUp()
{
	stop();
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteProgram(vertexShaderID);
	glDeleteProgram(fragmentShaderID);
	glDeleteProgram(programID);
}

int ShaderProgram::getUniformLocation(string uniformName)
{
	return glGetUniformLocation(programID, uniformName.c_str());
}

void ShaderProgram::bindAttribute(int attribute, string variableName)
{
	glBindAttribLocation(programID, attribute, variableName.c_str());
}

void ShaderProgram::loadInt(int location, GLint value)
{
	glUniform1i(location, value);
}

void ShaderProgram::loadFloat(int location, GLfloat value)
{
	glUniform1f(location, value);
}

void ShaderProgram::loadVector(int location, glm::vec3& vec)
{
	glUniform3f(location, vec.x, vec.y, vec.z);
}

void ShaderProgram::load2DVector(int location, glm::vec2& vec)
{
	glUniform2f(location, vec.x, vec.y);
}

void ShaderProgram::loadVector(int location, glm::vec4& vec)
{
	glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
}

void ShaderProgram::loadBoolean(int location, bool value)
{
	GLfloat toLoad = (value ? 1 : 0);
	glUniform1f(location, toLoad);
}

// value needs to have 16 components for a 4 x 4 matrix
void ShaderProgram::loadMatrix(int location, glm::mat4& matrix)
{
	glUniformMatrix4fv(location, 1, false, &matrix[0][0]);
}

int ShaderProgram::loadShader(string fileName, GLenum type)
{
	string src = readShaderSource(fileName);

	const char *shaderSource = src.c_str();

	GLuint shaderID = glCreateShader(type);
	glShaderSource(shaderID, 1, &shaderSource, NULL);
	glCompileShader(shaderID);
	GLint status;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
		GLchar infoLog[1024];
		GLsizei length;
		glGetShaderInfoLog(shaderID, sizeof(infoLog), &length, infoLog);
		string s(infoLog);
		cerr << s << endl;
		cerr << "Could not compile shader in file " + fileName << endl;
		exit(1);
	}

	return shaderID;
}

string ShaderProgram::readShaderSource(string fileName)
{
	ifstream inFile(fileName, ios::in);

	if (!inFile) {
		cerr << "ShaderProgram: File " << fileName << " could not be opened" << endl;
		exit(1);
	}

	string shaderSource, line;

	while ( !inFile.eof() ) {
		getline(inFile, line);
		shaderSource += line + "\n";
	}

	return shaderSource;
}
