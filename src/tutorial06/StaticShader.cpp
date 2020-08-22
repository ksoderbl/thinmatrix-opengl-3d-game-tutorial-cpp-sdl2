
#include "StaticShader.h"

const string VERTEX_FILE = "shaders/vertexShader.glsl";
const string FRAGMENT_FILE = "shaders/fragmentShader.glsl";

StaticShader::StaticShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE)
{
	;
}

void StaticShader::bindAttributes()
{
	ShaderProgram::bindAttribute(0, "position");
}

