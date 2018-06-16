#define DATADIR "../data"

#include "DisplayManager.h"
#include "RawModel.h"
#include "Loader.h"
#include "EntityRenderer.h"
#include "StaticShader.h"
#include "ModelTexture.h"
#include "TexturedModel.h"
#include "Keyboard.h"
#include "OBJLoader.h"
#include "MasterRenderer.h"

static bool pausing = false;
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

	case SDLK_SPACE:
	case SDLK_p:
	case SDLK_PAUSE:
		pausing = !pausing;
		break;
	case SDLK_r:
		//reset
		break;

	default:
		;
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

	case SDLK_SPACE:
	case SDLK_p:
	case SDLK_PAUSE:
		break;
	case SDLK_r:
		//reset
		break;

	default:
		;
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
			;
		}
		
		else if (event.type == SDL_MOUSEMOTION)
		{
			if (event.motion.state & SDL_BUTTON_LMASK) {
				; //mouseMotionEvent(event.motion);
			}
		}
		
		else if (event.type == SDL_WINDOWEVENT)
		{
			
			int w, h;
			switch (event.window.event) {
			case SDL_WINDOWEVENT_SIZE_CHANGED:
			case SDL_WINDOWEVENT_RESIZED:
				w = event.window.data1;
				h = event.window.data2;
				
				glViewport(0,0,w,h);
				break;
			default:
				break;
			}
			
		}
	}
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
	OBJLoader objLoader;

	RawModel* model = objLoader.loadObjModel("stall", loader);
	
	GLuint textureID = loader.loadTexture("stallTexture");
	ModelTexture texture = ModelTexture(textureID);
	TexturedModel staticModel = TexturedModel(*model, texture);
	texture.setShineDamper(10);
	texture.setReflectivity(1);

	Light light = Light(glm::vec3(0, 1000, 0), glm::vec3(1, 1, 1));

	GLuint terrainTextureID = loader.loadTexture("grass");
	ModelTexture terrainTexture = ModelTexture(terrainTextureID);
	Terrain terrain(0, 0, loader, terrainTexture);
	Terrain terrain2(-1, 0, loader, terrainTexture);
	Terrain terrain3(-1, -1, loader, terrainTexture);
	Terrain terrain4(0, -1, loader, terrainTexture);
	
	Camera camera;

	vector<Entity*> allEntities;
	srand(time(NULL));

	for (int i = 0; i < 2000; i++) {
		GLfloat x = my_rand() * 1500 - 750;
		GLfloat y = my_rand() * 3000;
		GLfloat z = my_rand() * 1500 - 750;
		
		allEntities.push_back(new Entity(staticModel, glm::vec3(x, y, z),
			my_rand() * 180, my_rand() * 180, 0, 1));
	}

	vector<Entity*>::iterator it;

	time_t oldt = 0, t;
	int fps = 0;

	MasterRenderer renderer;

	while (!isCloseRequested) {
		checkEvents(keyboard);
		
		camera.move(keyboard);

		renderer.processTerrain(terrain);
		renderer.processTerrain(terrain2);
		renderer.processTerrain(terrain3);
		renderer.processTerrain(terrain4);

		for (it = allEntities.begin(); it != allEntities.end(); it++) {
			Entity *entity = *it;
			
			if (!pausing) {
				entity->increasePosition(0.0, -2, 0.0);
				glm::vec3& pos = entity->getPosition();
				if (pos[1] < 0)
					entity->increasePosition(0.0, 3000, 0.0);
				entity->increaseRotation(2.0, 1.5, 1.0);
			}
			renderer.processEntity(*entity);
		}

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
