#ifndef LINE_H
#define LINE_H

#include "../Headers.h"

#include "Word.h"

/**
 * Represents a line of text during the loading of a text.
 */
class Line {
public:
	Line(double spaceWidth, double fontSize, double maxLength);
	bool attemptToAddWord(Word word);
	double getMaxLength();
	double getLineLength();
	vector<Word>& getWords();
private:
	double maxLength;
	double spaceSize;

	vector<Word> words;
	double currentLineLength = 0;
};

#endif
