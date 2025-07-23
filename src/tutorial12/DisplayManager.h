#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include "Headers.h"

class DisplayManager {
private:
	SDL_Window *window;
	SDL_GLContext glContext;
public:
	void createDisplay();

	void updateDisplay();

	void closeDisplay();
};

#endif
