#ifndef TEXTMESHCREATOR_H
#define TEXTMESHCREATOR_H

#include "../Headers.h"

#include "GUIText.h"
#include "TextMeshData.h"
#include "MetaFile.h"
#include "Line.h"

class TextMeshCreator {
public:
	static constexpr double LINE_HEIGHT = 0.03f;
	static constexpr int SPACE_ASCII = 32;
  
	TextMeshCreator(string metaFile);
	TextMeshData* createTextMesh(GUIText* text);
private:
	vector<Line*>* createStructure(GUIText *text);
	void completeStructure(vector<Line*>* lines, Line* currentLine,
		Word* currentWord, GUIText* text);
	TextMeshData* createQuadVertices(GUIText* text, vector<Line*>* lines);
	void addVerticesForCharacter(double cursorX, double cursorY, 
		Character character, double fontSize,
		vector<GLfloat>& vertices);
	void addVertices(vector<GLfloat>& vertices, double x, double y, double maxX, double maxY);
	void addTexCoords(vector<GLfloat>& texCoords, double x, double y, double maxX, double maxY);

	MetaFile *metaData;
};

#endif
