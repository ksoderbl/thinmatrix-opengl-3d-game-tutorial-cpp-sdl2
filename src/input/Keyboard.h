#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../Headers.h"

class Keyboard {
public:
	Keyboard();
	bool isKeyDown(SDL_Keycode sym);
	void setKeyDown(SDL_Keycode sym, bool isDown);
private:
	map<SDL_Keycode,bool> *keys;
};

extern Keyboard keyboard;

#endif
