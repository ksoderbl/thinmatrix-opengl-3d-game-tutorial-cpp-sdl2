#define DATADIR "../data"

#include "DisplayManager.h"
#include "RawModel.h"
#include "Loader.h"
#include "Renderer.h"
#include "StaticShader.h"

#include <cassert>
#include <cmath>
#include <ctime>
#include <csignal>
#include <cstdarg>
#include <cstdlib>

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
			}
			*/
		}
	}
	
	//if (currentEffect)
	//	currentEffect->drawFrame();
}


int main(int argc, char *argv[])
{
	DisplayManager manager;
	Loader loader;
	Renderer renderer;
	StaticShader shader;
	
	srand(time(NULL));
  
	manager.createDisplay();
	
	cout << "createDisplay OK"  << endl;
	
	vector<GLfloat> vertices = {
		-0.5f, 0.5f, 0.0f,  // V0
		-0.5f, -0.5f, 0.0f, // V1
		0.5f, -0.5f, 0.0f,  // V2
		0.5f, 0.5f, 0.0f    // V3
	};

	//  V0     V3
	//
	//  V1     V2

	vector<GLuint> indices = {
		0, 1, 3, // Top left triangle
		3, 1, 2  // Bottom right triangle
	};





	shader.LoadShaders();
        
	RawModel* model = loader.loadToVAO(vertices, indices);
    
	cout << "loadToVao OK"  << endl;
    
	while (!isCloseRequested) {
		renderer.prepare();
		
		// game logic
		checkEvents();
		
		renderer.render(model, shader.getShaderProgram());
		manager.updateDisplay();
	}

	loader.cleanUp();

	manager.closeDisplay();
	
	return 0;
}
