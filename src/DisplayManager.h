#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>

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
