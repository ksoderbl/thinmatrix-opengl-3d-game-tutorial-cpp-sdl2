#ifndef GUITEXTURE_H
#define GUITEXTURE_H

#include "Headers.h"

class GuiTexture {
public:
	GuiTexture(GLuint textureID, glm::vec2& position, glm::vec2& scale);
	GLuint getTextureId();
	glm::vec2& getPosition();
	glm::vec2& getScale();
private:
	GLuint textureID;
	glm::vec2 position;
	glm::vec2 scale;
};

#endif
