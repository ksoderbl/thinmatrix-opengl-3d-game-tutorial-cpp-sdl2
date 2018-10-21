#include "TextureData.h"

TextureData::TextureData(GLubyte* buffer, GLsizei width, GLsizei height)
{
	this->buffer = buffer;
	this->width = width;
	this->height = height;
}
GLsizei TextureData::getWidth()
{
	return width;
}
GLsizei TextureData::getHeight()
{
	return height;
}
GLubyte* TextureData::getBuffer()
{
	return buffer;
}
