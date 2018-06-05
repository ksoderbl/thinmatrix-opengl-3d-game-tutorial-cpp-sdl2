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
#include "MasterRenderer.h"

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

static GLfloat my_rand()
{
	int x = rand();
	GLfloat f = (GLfloat)x / RAND_MAX;
	return f;
}

int main(int argc, char *argv[])
{
	DisplayManager manager;

	manager.createDisplay();

	Keyboard keyboard;
	Loader loader;
	//StaticShader shader;
	//Renderer renderer(shader);
	OBJLoader objLoader;

	RawModel* model = objLoader.loadObjModel("stall", loader);
	
	GLuint textureID = loader.loadTexture("stallTexture");
	ModelTexture texture = ModelTexture(textureID);
	TexturedModel staticModel = TexturedModel(*model, texture);
	texture.setShineDamper(10);
	texture.setReflectivity(1);

	Light light = Light(glm::vec3(200, 200, 100), glm::vec3(1, 1, 1));
	
	Camera camera;

	vector<Entity*> allCubes;
	srand(time(NULL));

	//Entity entity = Entity(staticModel, glm::vec3(0, -4, -25), 0, 0, 0, 1);
	for (int i = 0; i < 20000; i++) {
		GLfloat x = my_rand() * 1000 - 500;
		GLfloat y = my_rand() * 1000 - 500;
		GLfloat z = my_rand() * -10000;
		allCubes.push_back(new Entity(staticModel, glm::vec3(x, y, z),
			my_rand() * 180, my_rand() * 180, 0, 1));
	}

	vector<Entity*>::iterator it;

	time_t oldt = 0, t;
	int fps = 0;

	MasterRenderer renderer;

	while (!isCloseRequested) {
		checkEvents(keyboard);
		
		//entity.increasePosition(0.0, 0.0, -0.01);
		//entity.increaseRotation(0.0, 1.0, 0.0);

		camera.move(keyboard);
		//renderer.prepare();
		//shader.start();
		//shader.loadLight(light);
		//shader.loadViewMatrix(camera);

		for (it = allCubes.begin(); it != allCubes.end(); it++) {
			Entity *entity = *it;
			entity->increasePosition(0.0, 0.0, 2);
			entity->increaseRotation(2.0, 1.5, 1.0);
			//renderer.render(*entity, shader);
			renderer.processEntity(*entity);
		}

		//shader.stop();
		
		renderer.render(light, camera);
		manager.updateDisplay();

		fps++;

		// FPS measurement
		t = time(NULL);
		if (t != oldt) {
			cout << "Current FPS: " << fps << "\n";
			oldt = t;
			fps = 0;
		}
	}

	renderer.cleanUp();
	loader.cleanUp();
	manager.closeDisplay();
	
	return 0;
}
