#include "Line.h"


/**
 * Creates an empty line.
 * 
 * @param spaceWidth
 *			- the screen-space width of a space character.
 * @param fontSize
 *			- the size of font being used.
 * @param maxLength
 *			- the screen-space maximum length of a line.
 */
Line::Line(double spaceWidth, double fontSize, double maxLength)
{
	this->spaceSize = spaceWidth * fontSize;
	this->maxLength = maxLength;
}

/**
 * Attempt to add a word to the line. If the line can fit the word in
 * without reaching the maximum line length then the word is added and the
 * line length increased.
 * 
 * @param word
 *			- the word to try to add.
 * @return {@code true} if the word has successfully been added to the line.
 */
bool Line::attemptToAddWord(Word word)
{
	double additionalLength = word.getWordWidth();
	additionalLength += !words.empty() ? spaceSize : 0;
	if (currentLineLength + additionalLength <= maxLength) {
		words.push_back(word);
		currentLineLength += additionalLength;
		return true;
	} else {
		return false;
	}
}

/**
 * @return The max length of the line.
 */
double Line::getMaxLength()
{
	return maxLength;
}

/**
 * @return The current screen-space length of the line.
 */
double Line::getLineLength()
{
	return currentLineLength;
}

/**
 * @return The list of words in the line.
 */
vector<Word>& Line::getWords()
{
	return words;
}
