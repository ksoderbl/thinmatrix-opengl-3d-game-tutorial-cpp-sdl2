#include "GUIText.h"
#include "TextMaster.h"

/**
 * Creates a new text, loads the text's quads into a VAO, and adds the text
 * to the screen.
 * 
 * @param text
 *            - the text.
 * @param fontSize
 *            - the font size of the text, where a font size of 1 is the
 *            default size.
 * @param font
 *            - the font that this text should use.
 * @param position
 *            - the position on the screen where the top left corner of the
 *            text should be rendered. The top left corner of the screen is
 *            (0, 0) and the bottom right is (1, 1).
 * @param maxLineLength
 *            - basically the width of the virtual page in terms of screen
 *            width (1 is full screen width, 0.5 is half the width of the
 *            screen, etc.) Text cannot go off the edge of the page, so if
 *            the text is longer than this length it will go onto the next
 *            line. When text is centered it is centered into the middle of
 *            the line, based on this line length value.
 * @param centered
 *            - whether the text should be centered or not.
 */
GUIText::GUIText( string text,
		  GLfloat fontSize,
		  FontType* font,
		  glm::vec2 position,
		  GLfloat maxLineLength,
		  bool centered)
{
	this->textString = text;
	this->fontSize = fontSize;
	this->font = font;
	this->position = position;
	this->lineMaxSize = maxLineLength;
	this->centerText = centered;
	textMaster.loadText(this);
}

/**
 * Remove the text from the screen.
 */
void GUIText::remove()
{
	textMaster.removeText(this);
}

/**
 * @return The font used by this text.
 */
FontType* GUIText::getFont()
{
	return font;
}

/**
 * Set the color of the text.
 * 
 * @param r
 *            - red value, between 0 and 1.
 * @param g
 *            - green value, between 0 and 1.
 * @param b
 *            - blue value, between 0 and 1.
 */
void GUIText::setColor(GLfloat r, GLfloat g, GLfloat b)
{
	color = glm::vec3(r, g, b);
}

/**
 * @return the color of the text.
 */
glm::vec3 GUIText::getColor()
{
	return color;
}

/**
 * @return The number of lines of text. This is determined when the text is
 *         loaded, based on the length of the text and the max line length
 *         that is set.
 */
int GUIText::getNumberOfLines()
{
	return numberOfLines;
}

/**
 * @return The position of the top-left corner of the text in screen-space.
 *         (0, 0) is the top left corner of the screen, (1, 1) is the bottom
 *         right.
 */
glm::vec2 GUIText::getPosition()
{
	return position;
}

/**
 * @return the ID of the text's VAO, which contains all the vertex data for
 *         the quads on which the text will be rendered.
 */
GLuint GUIText::getMesh()
{
	return textMeshVao;
}

/**
 * Set the VAO and vertex count for this text.
 * 
 * @param vao
 *            - the VAO containing all the vertex data for the quads on
 *            which the text will be rendered.
 * @param verticesCount
 *            - the total number of vertices in all of the quads.
 */
void GUIText::setMeshInfo(GLuint vao, int verticesCount)
{
	this->textMeshVao = vao;
	this->vertexCount = verticesCount;
}

/**
 * @return The total number of vertices of all the text's quads.
 */
int GUIText::getVertexCount()
{
	return vertexCount;
}

/**
 * @return the font size of the text (a font size of 1 is normal).
 */
int GUIText::getFontSize()
{
	return fontSize;
}

/**
 * Sets the number of lines that this text covers (method used only in
 * loading).
 * 
 * @param number
 */
void GUIText::setNumberOfLines(int number)
{
	this->numberOfLines = number;
}

/**
 * @return {@code true} if the text should be centered.
 */
bool GUIText::isCentered()
{
	return centerText;
}

/**
 * @return The maximum length of a line of this text.
 */
GLfloat GUIText::getMaxLineSize()
{
	return lineMaxSize;
}

/**
 * @return The string of text.
 */
string GUIText::getTextString()
{
	return textString;
}
