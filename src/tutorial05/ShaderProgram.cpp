
#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(string vertexFile, string fragmentFile)
{
	
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

void ShaderProgram::bindAttribute(int attribute, string variableName)
{
	glBindAttribLocation(programID, attribute, variableName.c_str());
}

// should be virtual
void ShaderProgram::bindAttributes()
{
	bindAttribute(0, "position");
}


int ShaderProgram::loadShader(string fileName, GLenum type)
{
	ifstream inFile(fileName, ios::in);
	
	if (!inFile) {
		cerr << "File " << fileName << " could not be opened" << endl;
		exit(1);
	}

	string shaderSource, line;

	while ( !inFile.eof() ) {
		getline(inFile, line);
		shaderSource += line + "\n";
	}
	
	GLuint shaderID = glCreateShader(type);
	
	const GLchar *shader = shaderSource.c_str();
	
	glShaderSource(shaderID, 1, &shader, NULL);
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

string ShaderProgram::ReadShaderSource(string fileName)
{
	ifstream inFile(fileName, ios::in);
	
	if (!inFile) {
		cerr << "File " << fileName << " could not be opened" << endl;
		exit(1);
	}

	string shaderSource, line;

	while ( !inFile.eof() ) {
		getline(inFile, line);
		shaderSource += line + "\n";
	}
	
	return shaderSource;	
}

void ShaderProgram::LoadShaders()
{
	string vsrc = ReadShaderSource("vertexShader.glsl");
	const char* vertex_shader = vsrc.c_str();
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	
	string fsrc = ReadShaderSource("fragmentShader.glsl");
	const char* fragment_shader = fsrc.c_str();
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);
    
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, fs);
	glAttachShader(shaderProgram, vs);
	glLinkProgram(shaderProgram);
    
	programID = shaderProgram;
}
