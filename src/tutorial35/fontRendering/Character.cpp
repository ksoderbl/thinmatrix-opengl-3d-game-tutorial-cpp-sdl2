#include "Character.h"    
/**
 * @param id
 *	    - the ASCII value of the character.
 * @param xTextureCoord
 *	    - the x texture coordinate for the top left corner of the
 *	    character in the texture atlas.
 * @param yTextureCoord
 *	    - the y texture coordinate for the top left corner of the
 *	    character in the texture atlas.
 * @param xTexSize
 *	    - the width of the character in the texture atlas.
 * @param yTexSize
 *	    - the height of the character in the texture atlas.
 * @param xOffset
 *	    - the x distance from the curser to the left edge of the
 *	    character's quad.
 * @param yOffset
 *	    - the y distance from the curser to the top edge of the
 *	    character's quad.
 * @param sizeX
 *	    - the width of the character's quad in screen space.
 * @param sizeY
 *	    - the height of the character's quad in screen space.
 * @param xAdvance
 *	    - how far in pixels the cursor should advance after adding
 *	    this character.
 */
Character::Character(int id, double xTextureCoord, double yTextureCoord,
	double xTexSize, double yTexSize, double xOffset, double yOffset,
	double sizeX, double sizeY, double xAdvance)
{
	this->id = id;
	this->xTextureCoord = xTextureCoord;
	this->yTextureCoord = yTextureCoord;
	this->xOffset = xOffset;
	this->yOffset = yOffset;
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->xMaxTextureCoord = xTexSize + xTextureCoord;
	this->yMaxTextureCoord = yTexSize + yTextureCoord;
	this->xAdvance = xAdvance;
}

int Character::getId()
{
	return id;
}

double Character::getxTextureCoord()
{
	return xTextureCoord;
}

double Character::getyTextureCoord()
{
	return yTextureCoord;
}

double Character::getXMaxTextureCoord()
{
	return xMaxTextureCoord;
}

double Character::getYMaxTextureCoord()
{
	return yMaxTextureCoord;
}

double Character::getxOffset()
{
	return xOffset;
}

double Character::getyOffset()
{
	return yOffset;
}

double Character::getSizeX()
{
	return sizeX;
}

double Character::getSizeY()
{
	return sizeY;
}

double Character::getxAdvance()
{
	return xAdvance;
}
