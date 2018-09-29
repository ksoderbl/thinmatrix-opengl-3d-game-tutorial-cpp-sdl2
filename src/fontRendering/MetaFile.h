#ifndef METAFILE_H
#define METAFILE_H

#include "../Headers.h"

#include "Character.h"


/**
 * Provides functionality for getting the values from a font file.
 */
class MetaFile {
public:
	MetaFile(string file);
	double getSpaceWidth();
	Character* getCharacter(int ascii);

private:
	bool processNextLine();
	int getValueOfVariable(string variable);
	vector<int> getValuesOfVariable(string variable);
	void close();
	bool openFile(string file);
	void loadPaddingData();
	void loadLineSizes();
	void loadCharacterData(int imageWidth);
	Character* loadCharacter(int imageSize);

	static constexpr int PAD_TOP = 0;
	static constexpr int PAD_LEFT = 1;
	static constexpr int PAD_BOTTOM = 2;
	static constexpr int PAD_RIGHT = 3;

	static constexpr int DESIRED_PADDING = 3;

	string SPLITTER = " ";
	string NUMBER_SEPARATOR = ",";

	double aspectRatio;
	double verticalPerPixelSize;
	double horizontalPerPixelSize;
	double spaceWidth;
	vector<int> padding;
	int paddingWidth;
	int paddingHeight;
	map<int, Character*> metaData;
	map<string, string> values;
	ifstream ifs; // input file
};

#endif
