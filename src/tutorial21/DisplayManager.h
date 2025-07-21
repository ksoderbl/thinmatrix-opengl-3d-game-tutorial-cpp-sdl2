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

private:
	SDL_Window *window;
	SDL_GLContext glContext;

	int FPS_CAP = 120;
	int WIDTH = 1280;
	int HEIGHT = 720;

	// e.g. SDL_WINDOWPOS_CENTERED, or SDL_WINDOWPOS_UNDEFINED
	int S_XPOS = SDL_WINDOWPOS_UNDEFINED;
	int S_YPOS = SDL_WINDOWPOS_UNDEFINED;
	string S_APPNAME = "OpenGL 3D Game Tutorial 21: Terrain Height Maps";
	
	long lastFrameTime;
	// render time of previous frame
	GLfloat delta;
};

#endif
