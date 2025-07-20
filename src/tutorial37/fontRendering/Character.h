#ifndef CHARACTER_H
#define CHARACTER_H

#include "../Headers.h"

class Character {
public:
	Character(int id, double xTextureCoord, double yTextureCoord,
		double xTexSize, double yTexSize, double xOffset, double yOffset,
		double sizeX, double sizeY, double xAdvance);
	int getId();
	double getxTextureCoord();
	double getyTextureCoord();
	double getXMaxTextureCoord();
	double getYMaxTextureCoord();
	double getxOffset();
	double getyOffset();
	double getSizeX();
	double getSizeY();
	double getxAdvance();

private:
	int id;
    double xTextureCoord;
    double yTextureCoord;
    double xMaxTextureCoord;
    double yMaxTextureCoord;
    double xOffset;
    double yOffset;
    double sizeX;
    double sizeY;
    double xAdvance;
};

#endif
