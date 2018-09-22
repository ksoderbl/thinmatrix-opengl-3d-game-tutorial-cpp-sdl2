#include "Mouse.h"

// global object so one doesn't have to pass it as an argument everywhere.
Mouse mouse;

Mouse::Mouse()
{
	dxTotal = 0;
	dyTotal = 0;
		
	wheelUp = 0;
	prevWheelUp = 0;
	wheelRight = 0;
	
	leftButtonIsDown = false;
	middleButtonIsDown = false;
	rightButtonIsDown = false;
}

void Mouse::move(int dx, int dy)
{
	dxTotal += dx;
	dyTotal += dy;
}

int Mouse::getDY()
{
	int retval = dyTotal;
	dyTotal = 0;
	return retval;
}

int Mouse::getDX()
{
	int retval = dxTotal;
	dxTotal = 0;
	return retval;
}

void Mouse::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}

int Mouse::getX()
{
	return this->x;
}

int Mouse::getY()
{
	return this->y;
}

void Mouse::incWheelUp(int up)
{
	wheelUp += up;
}

int Mouse::getWheelUp()
{
	return wheelUp;
}

// Return how much the mouse wheel was moved since this function
// was last called.
int Mouse::getDWheel()
{
	int retval = wheelUp - prevWheelUp;
	prevWheelUp = wheelUp;
	return retval;
}

void Mouse::incWheelRight(int right)
{
	wheelRight += right;
}

int Mouse::getWheelRight()
{
	return wheelRight;
}


void Mouse::setButtonState(Uint8 button, bool isDown)
{
	switch (button) {
	case SDL_BUTTON_LEFT:
		leftButtonIsDown = isDown;
		break;
	case SDL_BUTTON_MIDDLE:
		middleButtonIsDown = isDown;
		break;
	case SDL_BUTTON_RIGHT:
		rightButtonIsDown = isDown;
		break;
	case SDL_BUTTON_X1:
	case SDL_BUTTON_X2:
	default:
		break;
	}
}

bool Mouse::isLeftButtonDown()
{
	return leftButtonIsDown;
}
bool Mouse::isMiddleButtonDown()
{
	return middleButtonIsDown;
}
bool Mouse::isRightButtonDown()
{
	return rightButtonIsDown;
}
