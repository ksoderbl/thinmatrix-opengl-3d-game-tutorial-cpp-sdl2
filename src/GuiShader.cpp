#include "GuiShader.h"

const string VERTEX_FILE = "guis/guiVertexShader.glsl";
const string FRAGMENT_FILE = "guis/guiFragmentShader.glsl";

GuiShader::GuiShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE)
{
	bindAttributes();
	linkProgram();
	getAllUniformLocations();
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

