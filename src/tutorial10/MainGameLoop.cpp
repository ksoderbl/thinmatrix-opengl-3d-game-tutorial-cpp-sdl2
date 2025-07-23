#define DATADIR "../data"

#include "DisplayManager.h"
#include "RawModel.h"
#include "Loader.h"
#include "Renderer.h"
#include "StaticShader.h"
#include "ModelTexture.h"
#include "TexturedModel.h"
#include "Keyboard.h"
#include "OBJLoader.h"

//static bool pausing = false;
static bool isCloseRequested = false;

/* ---------------------------------------------------------------------- */

static void handle_keydown(Keyboard& keyboard, SDL_KeyboardEvent key)
{
	keyboard.setKeyDown(key.keysym.sym, true);
	
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

static void handle_keyup(Keyboard& keyboard, SDL_KeyboardEvent key)
{
	keyboard.setKeyDown(key.keysym.sym, false);
	
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


void checkEvents(Keyboard& keyboard)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			isCloseRequested = true;
		
		else if (event.type == SDL_KEYDOWN)
		{
			handle_keydown(keyboard, event.key);
		}

		else if (event.type == SDL_KEYUP)
		{
			handle_keyup(keyboard, event.key);
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

	srand(time(NULL));
  
	manager.createDisplay();

	Keyboard keyboard;
	Loader loader;
	StaticShader shader;
	Renderer renderer(shader);
	OBJLoader objLoader;

	RawModel* model = objLoader.loadObjModel("stall", loader);
	
	GLuint textureID = loader.loadTexture("stallTexture");
	
	ModelTexture texture = ModelTexture(textureID);
	
	TexturedModel staticModel = TexturedModel(*model, texture);

	Entity entity = Entity(staticModel, glm::vec3(0, 0, -20), 0, 0, 0, 1);
	
	Camera camera;

	while (!isCloseRequested) {
		checkEvents(keyboard);
		
		//entity.increasePosition(0.0, 0.0, -0.01);
		entity.increaseRotation(0.0, 1.0, 0.0);

		camera.move(keyboard);
		renderer.prepare();
		shader.start();
		shader.loadViewMatrix(camera);
		renderer.render(entity, shader);
		shader.stop();
		
		manager.updateDisplay();
	}

	shader.cleanUp();
	loader.cleanUp();
	manager.closeDisplay();
	
	return 0;
}
