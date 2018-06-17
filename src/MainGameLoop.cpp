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
	srand(time(NULL));

	Keyboard keyboard;
	Loader loader;
	OBJLoader objLoader;
	vector<Entity*> allEntities;

	// stall
	RawModel* stallRawModel = objLoader.loadObjModel("stall", loader);
	GLuint stallTextureID = loader.loadTexture("stallTexture");
	ModelTexture stallModelTexture = ModelTexture(stallTextureID);
	TexturedModel stallTexturedModel = TexturedModel(*stallRawModel, stallModelTexture);
	stallModelTexture.setShineDamper(10);
	stallModelTexture.setReflectivity(1);

	for (int i = 0; i < 500; i++) {
		GLfloat x = my_rand() * 1500 - 750;
		GLfloat y = my_rand() * 3000;
		GLfloat z = my_rand() * 1500 - 750;
		allEntities.push_back(new Entity(stallTexturedModel, glm::vec3(x, y, z),
			my_rand() * 180, my_rand() * 180, 0, 2));
	}

	// terrain
	GLuint terrainTextureID = loader.loadTexture("grass");
	ModelTexture terrainModelTexture = ModelTexture(terrainTextureID);
	Terrain terrain(0, 0, loader, terrainModelTexture);
	Terrain terrain2(-1, 0, loader, terrainModelTexture);
	Terrain terrain3(-1, -1, loader, terrainModelTexture);
	Terrain terrain4(0, -1, loader, terrainModelTexture);

	// tree
	RawModel* treeRawModel = objLoader.loadObjModel("tree", loader);
	GLuint treeTextureID = loader.loadTexture("tree");
	ModelTexture treeModelTexture = ModelTexture(treeTextureID);
	TexturedModel treeTexturedModel = TexturedModel(*treeRawModel, treeModelTexture);
	treeModelTexture.setShineDamper(40);
	treeModelTexture.setReflectivity(0.3);

	for (int i = 0; i < 1000; i++) {
		GLfloat x = my_rand() * 8000 - 4000;
		GLfloat y = 0;
		GLfloat z = my_rand() * 8000 - 4000;
		allEntities.push_back(new Entity(treeTexturedModel, glm::vec3(x, y, z),
			0, 0, 0, my_rand() * 15 + 5));
	}

	// grass

	Light light = Light(glm::vec3(0, 1000, 0), glm::vec3(1, 1, 1));
	Camera camera;

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
				if (&(entity->getModel()) == &stallTexturedModel) {
					entity->increasePosition(0.0, -2, 0.0);
					glm::vec3& pos = entity->getPosition();
					if (pos[1] < 0)
						entity->increasePosition(0.0, 3000, 0.0);
					entity->increaseRotation(2.0, 1.5, 1.0);
				}
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
