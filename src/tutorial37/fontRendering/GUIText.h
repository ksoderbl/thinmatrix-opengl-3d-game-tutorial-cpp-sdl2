#ifndef GUITEXT_H
#define GUITEXT_H

#include "../Headers.h"

//#include "FontType.h"

class FontType;

class GUIText {
public:
	GUIText(string text,
		GLfloat fontSize,
		FontType* font,
		glm::vec2 position,
		GLfloat maxLineLength,
		bool centered);
	void remove();
	FontType* getFont();
	glm::vec3 getColor();
	void setColor(GLfloat r, GLfloat g, GLfloat b);
	int getNumberOfLines();
	glm::vec2 getPosition();
	GLuint getMesh();
	void setMeshInfo(GLuint vao, int verticesCount);
	int getVertexCount();
	int getFontSize();
	void setNumberOfLines(int number);
	bool isCentered();
	GLfloat getMaxLineSize();
	string getTextString();
private:
	string textString;
	GLfloat fontSize;
	GLuint textMeshVao;
	int vertexCount;
	glm::vec3 color = glm::vec3(0, 0, 0);
	glm::vec2 position;
	GLfloat lineMaxSize;
	int numberOfLines;

	FontType* font;

	bool centerText = false;
};

#endif
