//namespace renderEngine;

#include "DisplayManager.h"




/* some initial values for the application */

const int WIDTH = 1280;
const int HEIGHT = 720;
const int FPS_CAP = 120;
// e.g. SDL_WINDOWPOS_CENTERED, or SDL_WINDOWPOS_UNDEFINED
const int S_XPOS = SDL_WINDOWPOS_UNDEFINED;
const int S_YPOS = SDL_WINDOWPOS_UNDEFINED;
const string S_APPNAME = "OpenGL 3D Game Tutorial 8: Model, View & Projection Matrices";


void DisplayManager::createDisplay()
{
	int val;
	GLenum error;
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "SDL_Init failed: " << SDL_GetError() << endl;
		exit(1);
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    
	Uint32 flags = SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE;
    
	window = SDL_CreateWindow(S_APPNAME.c_str(), S_XPOS, S_YPOS, WIDTH, HEIGHT, flags);
	if (!window) {
		cerr << "Create window failed: " << SDL_GetError() << endl;
		exit(1);
	}
	
	glContext = SDL_GL_CreateContext(window);
	if (!glContext) {
		cerr << "Create GL context failed: " << SDL_GetError() << endl;
		exit(1);
	}

	// Init GLEW after creating gl context
	glewExperimental = GL_TRUE; 
		
	// $ glewinfo | less
	error = glewInit();
	if (error != GLEW_OK) {
		cerr << "glewInit error: " << glewGetErrorString(error)  << endl;
		exit(1);
	}
	
	val = SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	if (val < 0) {
		cerr << "Double buffering failed: " << SDL_GetError() << endl;
		exit(1);
	}
	
	val = SDL_GL_SetSwapInterval(1);
	if (val < 0) {
		cerr << "Synchronizing with vertical retrace failed: " << SDL_GetError() << endl;
		exit(1);
	}

}

void DisplayManager::updateDisplay()
{
	SDL_GL_SwapWindow(window); // should sync with max FPS_CAP
}

void DisplayManager::closeDisplay()
{
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

