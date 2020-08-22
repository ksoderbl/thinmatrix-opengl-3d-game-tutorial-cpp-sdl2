
#include "StaticShader.h"

const string VERTEX_FILE = "shaders/vertexShader.glsl";
const string FRAGMENT_FILE = "shaders/fragmentShader.glsl";

StaticShader::StaticShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE)
{
	//ShaderProgram::initialize();
}

/*
void StaticShader::bindAttributes()
{
	ShaderProgram::bindAttribute(0, "position");
}
*/

