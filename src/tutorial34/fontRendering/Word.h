#ifndef WORD_H
#define WORD_H

#include "../Headers.h"

#include "Character.h"

/**
 * During the loading of a text this represents one word in the text.
 */
class Word {
public:
	Word(double fontSize);
	void addCharacter(Character character);
	vector<Character> getCharacters();
	double getWordWidth();

private:
	vector<Character> characters;
	double width = 0;
	double fontSize;	
};

#endif
