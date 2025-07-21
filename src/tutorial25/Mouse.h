#ifndef MOUSE_H
#define MOUSE_H

#include "Headers.h"

class Mouse {
public:
	Mouse();
	
	int getDY();
	int getDX();
	void move(int dx, int dy);
	void incWheelUp(int up);
	int getWheelUp();
	int getDWheel();
	void incWheelRight(int right);
	int getWheelRight();
	void setButtonState(Uint8 button, bool isDown);
	bool isLeftButtonDown();
	bool isMiddleButtonDown();
	bool isRightButtonDown();

private:
	int dxTotal;
	int dyTotal;

	int wheelUp;
	int prevWheelUp;
	int wheelRight;
	
	bool leftButtonIsDown;
	bool middleButtonIsDown;
	bool rightButtonIsDown;
};

#endif
