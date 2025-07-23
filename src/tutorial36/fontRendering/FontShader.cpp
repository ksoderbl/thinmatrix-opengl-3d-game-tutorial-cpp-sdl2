#include "FontShader.h"

const string VERTEX_FILE = "fontRendering/fontVertex.glsl";
const string FRAGMENT_FILE = "fontRendering/fontFragment.glsl";

FontShader::FontShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE)
{
	bindAttributes();
	linkProgram();
	getAllUniformLocations();
}

void FontShader::bindAttributes()
{
	bindAttribute(0, "position");
	bindAttribute(1, "textureCoords");
}

void FontShader::getAllUniformLocations()
{
	location_color = getUniformLocation("color");
	location_translation = getUniformLocation("translation");
}

void FontShader::loadColor(glm::vec3 color)
{
	loadVector(location_color, color);
}

void FontShader::loadTranslation(glm::vec2 translation)
{
	load2DVector(location_translation, translation);
}
