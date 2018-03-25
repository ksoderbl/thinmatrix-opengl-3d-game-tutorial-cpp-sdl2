
#include "StaticShader.h"

const string VERTEX_FILE = "vertexShader.txt";
const string FRAGMENT_FILE = "fragmentShader.txt";

StaticShader::StaticShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE)
{
	;
}

/*
void StaticShader::bindAttributes()
{
	ShaderProgram::bindAttribute(0, "position");
}
*/
