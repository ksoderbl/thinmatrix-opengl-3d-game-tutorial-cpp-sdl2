#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "Headers.h"

class Keyboard {
public:
	Keyboard();
	bool isKeyDown(SDL_Keycode sym);
	void setKeyDown(SDL_Keycode sym, bool isDown);
private:
	// this code handles only sdl keycodes that are < NUM_KEYS
	static constexpr int NUM_KEYS = 256; 
	bool keyIsDown[NUM_KEYS];
};

#endif
