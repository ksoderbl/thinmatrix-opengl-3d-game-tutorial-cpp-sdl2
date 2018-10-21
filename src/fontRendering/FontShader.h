#ifndef FONTSHADER_H
#define FONTSHADER_H

#include "../shaders/ShaderProgram.h"

class FontShader: public ShaderProgram
{
public:
	FontShader();
	void bindAttributes();
	void getAllUniformLocations();
	void loadColor(glm::vec3 color);
	void loadTranslation(glm::vec2 translation);
private:
	int location_color;
	int location_translation;
};

#endif
