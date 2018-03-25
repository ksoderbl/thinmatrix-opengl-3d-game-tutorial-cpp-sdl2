#include <iostream>
#include <string>

using std::cout;
using std::cerr;
using std::endl;
using std::string;

#include <GL/gl.h>
#include <GL/glu.h>

#include <SDL2/SDL.h>

#include <cassert>
#include <cmath>
#include <ctime>
#include <csignal>
#include <cstdarg>
#include <cstdlib>

#include "MainGameLoop.h"
#include "DisplayManager.h"

static bool pausing = false;
static bool isCloseRequested = false;

/* ---------------------------------------------------------------------- */

static void handle_keydown(SDL_KeyboardEvent key)
{
	//cout << "KEYDOWN, current effect = " << currentEffectIndex << endl;

	if (pausing) {
		cout << "pause keyboard cb\n";

		switch (key.keysym.sym) {
			/* quit pausing */
		case SDLK_SPACE:
		case SDLK_p:
		case SDLK_PAUSE:
		case SDLK_ESCAPE:
			pausing = false;
			break;
		default:
			break;
		}

		return;
	}


	// not pausing
	
	switch (key.keysym.sym) {
	case SDLK_ESCAPE:
		isCloseRequested = true;
		break;
	case SDLK_m:
		//messages_toggle();
		break;

	case SDLK_p:
	case SDLK_PAUSE:
		// TODO: pause_request();
		break;
	case SDLK_r:
		//if (currentEffect)
		//	currentEffect->reset();
		break;

	default:
		;
		//if (currentEffect)
		//	currentEffect->keyboardEvent(key);
	}
}


void checkEvents(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			isCloseRequested = true;
		
		else if (event.type == SDL_KEYDOWN)
		{
			handle_keydown(event.key);
		}
		
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			//cout << "mouse button down, current effect is " << currentEffectIndex << endl;
			//if (currentEffect)
			//	currentEffect->mouseButtonDownEvent(event.button);
		}
		
		else if (event.type == SDL_MOUSEMOTION)
		{
			if (event.motion.state & SDL_BUTTON_LMASK) {
				//if (currentEffect)
				//		currentEffect->mouseMotionEvent(event.motion);
			}
		}
		
		else if (event.type == SDL_WINDOWEVENT)
		{
			/*
			int w, h;
			switch (event.window.event) {
			case SDL_WINDOWEVENT_SIZE_CHANGED:
			case SDL_WINDOWEVENT_RESIZED:
				w = event.window.data1;
				h = event.window.data2;
				
				//if (currentEffect)
				//	currentEffect->resize(w, h);
				break;
			default:
				break;
			}*/
		}
	}
	
	//if (currentEffect)
	//	currentEffect->drawFrame();
}


int main(int argc, char *argv[])
{
	DisplayManager dm;
  
	srand(time(NULL));
	
	dm.createDisplay();
    
	while (!isCloseRequested) {

		checkEvents();
		// game logic
		// render
		dm.updateDisplay();
	}

	dm.closeDisplay();
	
	return 0;
}
