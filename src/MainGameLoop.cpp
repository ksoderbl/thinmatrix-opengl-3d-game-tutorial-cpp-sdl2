#define DATADIR "../data"

#include "DisplayManager.h"
#include "RawModel.h"
#include "Loader.h"
#include "EntityRenderer.h"
#include "StaticShader.h"
#include "ModelTexture.h"
#include "TexturedModel.h"
#include "Keyboard.h"
#include "OBJFileLoader.h"
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
	OBJFileLoader objLoader;
	vector<Entity*> allEntities;

	// stall
	//RawModel* stallRawModel = objLoader.loadObjModel("stall", loader);
	ModelData *stallModelData = objLoader.loadOBJ("stall");
	RawModel* stallRawModel = loader.loadToVAO(stallModelData->getVertices(), stallModelData->getTextureCoords(),
		stallModelData->getNormals(), stallModelData->getIndices());
	GLuint stallTextureID = loader.loadTexture("stallTexture");
	ModelTexture stallModelTexture = ModelTexture(stallTextureID);
	TexturedModel stallTexturedModel = TexturedModel(*stallRawModel, stallModelTexture);
	stallModelTexture.setShineDamper(10);
	stallModelTexture.setReflectivity(1);

	for (int i = 0; i < 100; i++) {
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
	//RawModel* treeRawModel = objLoader.loadObjModel("tree", loader);
	ModelData *treeModelData = objLoader.loadOBJ("tree");
	RawModel* treeRawModel = loader.loadToVAO(treeModelData->getVertices(), treeModelData->getTextureCoords(),
		treeModelData->getNormals(), treeModelData->getIndices());
	GLuint treeTextureID = loader.loadTexture("tree");
	ModelTexture treeModelTexture = ModelTexture(treeTextureID);
	TexturedModel treeTexturedModel = TexturedModel(*treeRawModel, treeModelTexture);
	//treeModelTexture.setShineDamper(4);
	//treeModelTexture.setReflectivity(0.3);

	for (int i = 0; i < 100; i++) {
		GLfloat x = my_rand() * 800 - 400;
		GLfloat y = 0;
		GLfloat z = my_rand() * 800 - 400;
		allEntities.push_back(new Entity(treeTexturedModel, glm::vec3(x, y, z),
			0, 0, 0, my_rand() * 4 + 4));
	}

	// low poly tree
	//RawModel* lowPolyTreeRawModel = objLoader.loadObjModel("lowPolyTree", loader);
	ModelData *lowPolyTreeModelData = objLoader.loadOBJ("lowPolyTree");
	RawModel* lowPolyTreeRawModel = loader.loadToVAO(lowPolyTreeModelData->getVertices(), lowPolyTreeModelData->getTextureCoords(),
		lowPolyTreeModelData->getNormals(), lowPolyTreeModelData->getIndices());
	GLuint lowPolyTreeTextureID = loader.loadTexture("lowPolyTree");
	ModelTexture lowPolyTreeModelTexture = ModelTexture(lowPolyTreeTextureID);
	TexturedModel lowPolyTreeTexturedModel = TexturedModel(*lowPolyTreeRawModel, lowPolyTreeModelTexture);
	//lowPolyTreeModelTexture.setShineDamper(4);
	//lowPolyTreeModelTexture.setReflectivity(0.3);

	for (int i = 0; i < 100; i++) {
		GLfloat x = my_rand() * 800 - 200;
		GLfloat y = 0;
		GLfloat z = my_rand() * 800 - 500;
		allEntities.push_back(new Entity(lowPolyTreeTexturedModel, glm::vec3(x, y, z),
			0, 0, 0, my_rand() * 0.5 + 0.3));
	}

	// grass
	//RawModel* grassRawModel = objLoader.loadObjModel("grassModel", loader);
	ModelData *grassModelData = objLoader.loadOBJ("grassModel");
	RawModel* grassRawModel = loader.loadToVAO(grassModelData->getVertices(), grassModelData->getTextureCoords(),
		grassModelData->getNormals(), grassModelData->getIndices());
	GLuint grassTextureID = loader.loadTexture("grassTexture");
	ModelTexture grassModelTexture = ModelTexture(grassTextureID);
	TexturedModel grassTexturedModel = TexturedModel(*grassRawModel, grassModelTexture);
	grassTexturedModel.getTexture().setHasTransparency(true);
	grassTexturedModel.getTexture().setUseFakeLighting(true);
	//grassModelTexture.setShineDamper(1);
	//grassModelTexture.setReflectivity(0.5);

	for (int i = 0; i < 200; i++) {
		GLfloat x = my_rand() * 1800 - 900;
		GLfloat y = 0;
		GLfloat z = my_rand() * 1800 - 900;
		allEntities.push_back(new Entity(grassTexturedModel, glm::vec3(x, y, z),
			0, 0, 0, my_rand() * 3 + 1));
	}

	// fern
	//RawModel* fernRawModel = objLoader.loadObjModel("fern", loader);
	ModelData *fernModelData = objLoader.loadOBJ("fern");
	RawModel* fernRawModel = loader.loadToVAO(fernModelData->getVertices(), fernModelData->getTextureCoords(),
		fernModelData->getNormals(), fernModelData->getIndices());
	GLuint fernTextureID = loader.loadTexture("fern");
	ModelTexture fernModelTexture = ModelTexture(fernTextureID);
	TexturedModel fernTexturedModel = TexturedModel(*fernRawModel, fernModelTexture);
	fernTexturedModel.getTexture().setHasTransparency(true);
	fernTexturedModel.getTexture().setUseFakeLighting(true);
	fernModelTexture.setShineDamper(1);
	fernModelTexture.setReflectivity(0);

	for (int i = 0; i < 200; i++) {
		GLfloat x = my_rand() * 1400 - 700;
		GLfloat y = 0;
		GLfloat z = my_rand() * 1400 - 700;
		allEntities.push_back(new Entity(fernTexturedModel, glm::vec3(x, y, z),
			0, 0, 0, my_rand() * 0.5 + 1));
	}

	// flower, using fern as raw model, seems to work
	//RawModel* flowerRawModel = objLoader.loadObjModel("fern", loader);
	ModelData *flowerModelData = objLoader.loadOBJ("fern");
	RawModel* flowerRawModel = loader.loadToVAO(flowerModelData->getVertices(), flowerModelData->getTextureCoords(),
		flowerModelData->getNormals(), flowerModelData->getIndices());
	GLuint flowerTextureID = loader.loadTexture("flower");
	ModelTexture flowerModelTexture = ModelTexture(flowerTextureID);
	TexturedModel flowerTexturedModel = TexturedModel(*flowerRawModel, flowerModelTexture);
	flowerTexturedModel.getTexture().setHasTransparency(true);
	flowerTexturedModel.getTexture().setUseFakeLighting(true);
	//flowerModelTexture.setShineDamper(1);
	//flowerModelTexture.setReflectivity(0.5);

	for (int i = 0; i < 200; i++) {
		GLfloat x = my_rand() * 1200 - 300;
		GLfloat y = 0;
		GLfloat z = my_rand() * 1700 - 900;
		allEntities.push_back(new Entity(flowerTexturedModel, glm::vec3(x, y, z),
			0, 0, 0, my_rand() * .3 + .1));
	}

	Light light = Light(glm::vec3(3000, 2000, 2000), glm::vec3(1, 1, 1));
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
