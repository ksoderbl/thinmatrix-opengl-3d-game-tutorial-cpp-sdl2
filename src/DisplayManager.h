#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include "Headers.h"

class DisplayManager {
public:
	void createDisplay();
	void updateDisplay();
	void closeDisplay();
	long getCurrentTime();
	GLfloat getFrameTimeSeconds();
	GLsizei getWidth() { return width; }
	GLsizei getHeight() { return height; }
	void setSize(GLsizei width, GLsizei height);

private:
	SDL_Window *window;
	SDL_GLContext glContext;

	int FPS_CAP = 120;
	GLsizei width = 1280;
	GLsizei height = 720;

	// e.g. SDL_WINDOWPOS_CENTERED, or SDL_WINDOWPOS_UNDEFINED
	int S_XPOS = SDL_WINDOWPOS_UNDEFINED;
	int S_YPOS = SDL_WINDOWPOS_UNDEFINED;

	long lastFrameTime;
	// render time of previous frame
	GLfloat delta;
	time_t oldt = 0;
	int fps = 0;
};

#endif
