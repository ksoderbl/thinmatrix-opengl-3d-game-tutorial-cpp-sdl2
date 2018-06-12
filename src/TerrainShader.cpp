
#include "TerrainShader.h"

const string VERTEX_FILE = "shaders/terrainVertexShader.txt";
const string FRAGMENT_FILE = "shaders/terrainFragmentShader.txt";

TerrainShader::TerrainShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE)
{
	//ShaderProgram::initialize();
}
