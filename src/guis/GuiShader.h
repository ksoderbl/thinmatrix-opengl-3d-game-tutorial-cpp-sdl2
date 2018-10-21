#ifndef GUISHADER_H
#define GUISHADER_H

#include "../shaders/ShaderProgram.h"

class GuiShader: public ShaderProgram
{
public:
	GuiShader();
	void bindAttributes();
	void getAllUniformLocations();
	void connectTextureUnits();
	void loadTransformationMatrix(glm::mat4& matrix);

private:
	int location_transformationMatrix;
};

#endif
