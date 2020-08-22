
#include "Headers.h"

class ShaderProgram
{
public:
	ShaderProgram(string vertexFile, string fragmentFile);
	
	void start();
	void stop();
	void cleanUp();
	void bindAttribute(int attribute, string variableName);
	//virtual 
	void bindAttributes();
	// = 0;
	
	int getShaderProgram() { return programID; }

private:
	int loadShader(string fileName, GLenum type);
	string readShaderSource(string fileName);
	
	int programID;
	int vertexShaderID;
	int fragmentShaderID;
};
