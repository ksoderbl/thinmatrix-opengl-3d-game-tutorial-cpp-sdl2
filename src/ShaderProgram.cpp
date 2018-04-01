
#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(string vertexFile, string fragmentFile)
{
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

int ShaderProgram::getUniformLocation(string uniformName)
{
	return glGetUniformLocation(programID, uniformName.c_str());
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
	bindAttribute(1, "textureCoords");
}

void ShaderProgram::loadFloat(int location, float value)
{
	glUniform1f(location, value);
}

void ShaderProgram::loadVector(int location, vector<GLfloat>& vec)
{
	glUniform3f(location, vec[0], vec[1], vec[2]);
}

void ShaderProgram::loadBoolean(int location, bool value)
{
	GLfloat toLoad = (value ? 1 : 0);
	glUniform1f(location, toLoad);
}

// value needs to have 16 components for a 4 x 4 matrix
void ShaderProgram::loadMatrix(int location, GLfloat matrix[16])
{
	glUniformMatrix4fv(location, 1, false, matrix);
}

void ShaderProgram::loadTransformationMatrix(GLfloat matrix[16])
{
	loadMatrix(location_transformationMatrix, matrix);
}

void ShaderProgram::getAllUniformLocations()
{
	cout << "getAllUniformLocations()" << endl;
	
	location_transformationMatrix = getUniformLocation("transformationMatrix");

	vector<GLfloat> tr = {1, 2, 3};

	glm::mat4 m = createTransformationMatrix(tr, 45.0, 90.0, 135.0, 2.0);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << "m[" << i << "," << j << "] = " << m[j][i] << " ";
		}
		cout << endl;
	}

	cout << "getAllUniformLocations() done" << endl;
	
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

