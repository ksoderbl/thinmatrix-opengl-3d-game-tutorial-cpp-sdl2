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
#include "TerrainTexture.h"
#include "TerrainTexturePack.h"
#include "Player.h"
#include "Mouse.h"
#include "GuiTexture.h"
#include "GuiRenderer.h"
#include "WaterRenderer.h"
#include "WaterShader.h"
#include "WaterTile.h"
#include "WaterFrameBuffers.h"

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

	case SDLK_PAUSE:
		break;
	case SDLK_r:
		//reset
		break;

	default:
		;
	}
}


void checkEvents(Keyboard& keyboard, Mouse& mouse, DisplayManager& display)
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

		else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
			/*
			string eventType = "";

			if (event.type == SDL_MOUSEBUTTONDOWN)
				eventType = "SDL_MOUSEBUTTONDOWN";
			if (event.type == SDL_MOUSEBUTTONUP)
				eventType = "SDL_MOUSEBUTTONUP";

			string type = "";
			if (event.button.type == SDL_MOUSEBUTTONDOWN)
				type = "SDL_MOUSEBUTTONDOWN";
			if (event.button.type == SDL_MOUSEBUTTONUP)
				type = "SDL_MOUSEBUTTONUP";

			cout << eventType << " event: type=" <<type<< "\n";

			string button = "";
			switch (event.button.button) {
				case SDL_BUTTON_LEFT: button = "SDL_BUTTON_LEFT"; break;
				case SDL_BUTTON_MIDDLE: button = "SDL_BUTTON_MIDDLE"; break;
				case SDL_BUTTON_RIGHT: button = "SDL_BUTTON_RIGHT"; break;
				case SDL_BUTTON_X1: button = "SDL_BUTTON_X1"; break;
				case SDL_BUTTON_X2: button = "SDL_BUTTON_X2"; break;
				default: break;
			}
			cout << eventType << " event: button=" <<button<< "\n";

			string state = "";
			switch (event.button.state) {
				case SDL_PRESSED: state = "SDL_PRESSED"; break;
				case SDL_RELEASED: state = "SDL_RELEASED"; break;
				default: break;
			}

			cout << eventType << " event: state=" <<state<< "\n";
			*/

			mouse.setButtonState(
				event.button.button, // SDL_BUTTON_LEFT etc.
				event.button.state == SDL_PRESSED);
		}

		else if (event.type == SDL_MOUSEMOTION)
		{
			Uint32 state = event.motion.state;

			//if (event.motion.state & SDL_BUTTON_LMASK) {
			//	; //mouseMotionEvent(event.motion);
			//}

			// for now: ignore mouse movement if a button is not pressed {
			if ((state & SDL_BUTTON_LMASK)
				|| (state & SDL_BUTTON_MMASK)
				|| (state & SDL_BUTTON_RMASK)) {
				mouse.move(event.motion.xrel, event.motion.yrel);
			}

			//int x = event.motion.x;
			//int y = event.motion.y;
			//mouse.setPosition(x, y);
		}
		else if (event.type == SDL_MOUSEWHEEL) {
			int x = event.wheel.x;
			int y = event.wheel.y;
			// ignore possibility of SDL_MOUSEWHEEL_FLIPPED at the moment
			if (y != 0) {
				mouse.incWheelUp(y);
			}
			if (x != 0) {
				mouse.incWheelRight(x);
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
				display.setSize(w, h);
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
	DisplayManager display;

	display.createDisplay();
	srand(time(NULL));

	Keyboard keyboard;
	Mouse mouse;
	Loader loader;

	// terrain texture stuff
	TerrainTexture backgroundTexture(loader.loadTexture("grassy2"));
	TerrainTexture rTexture(loader.loadTexture("dirt"));
	TerrainTexture gTexture(loader.loadTexture("pinkFlowers"));
	TerrainTexture bTexture(loader.loadTexture("path"));
	TerrainTexturePack texturePack(backgroundTexture, rTexture, gTexture, bTexture);
	TerrainTexture blendMap(loader.loadTexture("blendMap"));

	vector<Terrain*> terrains;
	Terrain terrain(0, 0, loader, texturePack, blendMap, "heightmap");
	Terrain terrain2(-1, 0, loader, texturePack, blendMap, "heightmap");
	Terrain terrain3(-1, -1, loader, texturePack, blendMap, "heightmap");
	Terrain terrain4(0, -1, loader, texturePack, blendMap, "heightmap");
	terrains.push_back(&terrain);
	terrains.push_back(&terrain2);
	terrains.push_back(&terrain3);
	terrains.push_back(&terrain4);

	OBJFileLoader objLoader;
	vector<Entity*> entities;

	// stall
	ModelData *stallModelData = objLoader.loadOBJ("stall");
	RawModel* stallRawModel = loader.loadToVAO(stallModelData->getVertices(), stallModelData->getTextureCoords(),
		stallModelData->getNormals(), stallModelData->getIndices());
	GLuint stallTextureID = loader.loadTexture("stallTexture");
	ModelTexture stallModelTexture = ModelTexture(stallTextureID);
	TexturedModel stallTexturedModel = TexturedModel(*stallRawModel, stallModelTexture);
	stallModelTexture.setShineDamper(10);
	stallModelTexture.setReflectivity(1);

	for (int i = 0; i < 0; i++) {
		GLfloat x = my_rand() * 350 - 175;
		GLfloat y = my_rand() * 250;
		GLfloat z = my_rand() * 350 - 175;
		entities.push_back(new Entity(stallTexturedModel, glm::vec3(x, y, z),
			my_rand() * 180, my_rand() * 180, 0, 2));
	}

	// pine, was tree
	ModelData *pineModelData = objLoader.loadOBJ("pine");
	RawModel* pineRawModel = loader.loadToVAO(pineModelData->getVertices(), pineModelData->getTextureCoords(),
		pineModelData->getNormals(), pineModelData->getIndices());
	GLuint pineTextureID = loader.loadTexture("pine");
	ModelTexture pineModelTexture = ModelTexture(pineTextureID);
	TexturedModel pineTexturedModel = TexturedModel(*pineRawModel, pineModelTexture);
	//pineModelTexture.setShineDamper(4);
	//pineModelTexture.setReflectivity(0.3);

	for (int i = 0; i < 40; i++) {
		GLfloat x = my_rand() * 800 - 400;
		GLfloat z = my_rand() * 800 - 400;
		GLfloat y = terrain4.getHeightOfTerrain(x, z);
		entities.push_back(new Entity(pineTexturedModel, glm::vec3(x, y, z),
			0, 0, 0, my_rand() * 1 + 1));
	}

	// low poly tree
	ModelData *lowPolyTreeModelData = objLoader.loadOBJ("lowPolyTree");
	RawModel* lowPolyTreeRawModel = loader.loadToVAO(lowPolyTreeModelData->getVertices(), lowPolyTreeModelData->getTextureCoords(),
		lowPolyTreeModelData->getNormals(), lowPolyTreeModelData->getIndices());
	GLuint lowPolyTreeTextureID = loader.loadTexture("lowPolyTree");
	ModelTexture lowPolyTreeModelTexture = ModelTexture(lowPolyTreeTextureID);
	TexturedModel lowPolyTreeTexturedModel = TexturedModel(*lowPolyTreeRawModel, lowPolyTreeModelTexture);
	lowPolyTreeModelTexture.setShineDamper(4);
	lowPolyTreeModelTexture.setReflectivity(0.3);

	for (int i = 0; i < 2; i++) {
		GLfloat x = my_rand() * 1800 - 900;
		GLfloat z = my_rand() * 1800 - 900;
		GLfloat y = terrain4.getHeightOfTerrain(x, z);
		entities.push_back(new Entity(lowPolyTreeTexturedModel, glm::vec3(x, y, z),
			0, my_rand() * 360, 0, my_rand() * 1 + 1));
	}

	// grass
	ModelData *grassModelData = objLoader.loadOBJ("grassModel");
	RawModel* grassRawModel = loader.loadToVAO(grassModelData->getVertices(), grassModelData->getTextureCoords(),
		grassModelData->getNormals(), grassModelData->getIndices());
	GLuint grassTextureID = loader.loadTexture("grassTexture");
	ModelTexture grassModelTexture = ModelTexture(grassTextureID);
	TexturedModel grassTexturedModel = TexturedModel(*grassRawModel, grassModelTexture);
	grassTexturedModel.getTexture().setHasTransparency(true);
	grassTexturedModel.getTexture().setUseFakeLighting(true);
	grassModelTexture.setShineDamper(1);
	grassModelTexture.setReflectivity(0.5);

	for (int i = 0; i < 100; i++) {
		GLfloat x = my_rand() * 2000 - 1000;
		GLfloat z = my_rand() * 2000 - 800;
		GLfloat y = terrain4.getHeightOfTerrain(x, z);
		entities.push_back(new Entity(grassTexturedModel, glm::vec3(x, y, z),
			0, my_rand() * 360, 0, my_rand() * 3 + 1));
	}

	// fern
	ModelData *fernModelData = objLoader.loadOBJ("fern");
	RawModel* fernRawModel = loader.loadToVAO(fernModelData->getVertices(), fernModelData->getTextureCoords(),
		fernModelData->getNormals(), fernModelData->getIndices());
	GLuint fernTextureID = loader.loadTexture("fern");
	ModelTexture fernTextureAtlas = ModelTexture(fernTextureID);
	fernTextureAtlas.setShineDamper(4);
	fernTextureAtlas.setReflectivity(0.1);
	fernTextureAtlas.setNumberOfRows(2);
	TexturedModel fernTexturedModel = TexturedModel(*fernRawModel, fernTextureAtlas);
	fernTexturedModel.getTexture().setHasTransparency(true);
	fernTexturedModel.getTexture().setUseFakeLighting(true);

	for (int i = 0; i < 120; i++) {
		GLfloat x = my_rand() * 1000 - 500;
		GLfloat z = my_rand() * 1000 - 500;
		GLfloat y = terrain4.getHeightOfTerrain(x, z);
		entities.push_back(new Entity(fernTexturedModel, glm::vec3(x, y, z),
			rand() % 4, 0,  my_rand() * 360, 0, my_rand() * 0.5 + 1));
	}

	// flower, using fern as raw model, seems to work
	ModelData *flowerModelData = objLoader.loadOBJ("fern");
	RawModel* flowerRawModel = loader.loadToVAO(flowerModelData->getVertices(), flowerModelData->getTextureCoords(),
		flowerModelData->getNormals(), flowerModelData->getIndices());
	GLuint flowerTextureID = loader.loadTexture("diffuse");
	ModelTexture flowerTextureAtlas = ModelTexture(flowerTextureID);
	flowerTextureAtlas.setShineDamper(5);
	flowerTextureAtlas.setReflectivity(0.2);
	flowerTextureAtlas.setNumberOfRows(2);
	TexturedModel flowerTexturedModel = TexturedModel(*flowerRawModel, flowerTextureAtlas);
	flowerTexturedModel.getTexture().setHasTransparency(true);
	flowerTexturedModel.getTexture().setUseFakeLighting(true);

	for (int i = 0; i < 40; i++) {
		GLfloat x = my_rand() * 1200 - 600;
		GLfloat z = my_rand() * 1200 - 600;
		GLfloat y = terrain4.getHeightOfTerrain(x, z);
		entities.push_back(new Entity(flowerTexturedModel, glm::vec3(x, y, z),
			rand() % 9, 0,  my_rand() * 360, 0, my_rand() * 1 + 1));
	}

	vector<Light*> lights;
	Light light = Light(glm::vec3(0, 3000, -7000), glm::vec3(1.0f, 1.0f, 1.0f));
	Light light2 = Light(glm::vec3(185, 10, -293), glm::vec3(2, 0, 0), glm::vec3(1, 0.01f, 0.002f));
	Light light3 = Light(glm::vec3(370, 17, -300), glm::vec3(0, 2, 2), glm::vec3(1, 0.01f, 0.002f));
	Light light4 = Light(glm::vec3(293, 7, -305),  glm::vec3(2, 2, 0), glm::vec3(1, 0.01f, 0.002f));
	lights.push_back(&light);
	lights.push_back(&light2);
	lights.push_back(&light3);
	lights.push_back(&light4);

	ModelData *lampModelData = objLoader.loadOBJ("lamp");
	RawModel* lampRawModel = loader.loadToVAO(lampModelData->getVertices(), lampModelData->getTextureCoords(),
		lampModelData->getNormals(), lampModelData->getIndices());
	GLuint lampTextureID = loader.loadTexture("lamp");
	ModelTexture lampModelTexture = ModelTexture(lampTextureID);
	TexturedModel lamp = TexturedModel(*lampRawModel, lampModelTexture);

	entities.push_back(new Entity(lamp, glm::vec3(185, -4.7f, -293), 0, 0, 0, 1));
	entities.push_back(new Entity(lamp, glm::vec3(370, 4.2f, -300), 0, 0, 0, 1));
	entities.push_back(new Entity(lamp, glm::vec3(293, -6.8f, -305), 0, 0, 0, 1));



	ModelData *playerModelData = objLoader.loadOBJ("person");
	RawModel* playerRawModel = loader.loadToVAO(playerModelData->getVertices(), playerModelData->getTextureCoords(),
		playerModelData->getNormals(), playerModelData->getIndices());
	GLuint playerTextureID = loader.loadTexture("playerTexture");
	ModelTexture playerModelTexture = ModelTexture(playerTextureID);
	TexturedModel playerTexturedModel = TexturedModel(*playerRawModel, playerModelTexture);
	playerModelTexture.setShineDamper(10);
	playerModelTexture.setReflectivity(1);

	Player player(playerTexturedModel, glm::vec3(100, 0, -50), 0, 180, 0, 0.6f);
	Camera camera(player);

	vector<GuiTexture*> guis;
	glm::vec2 position(0.7f, 0.5f);
	glm::vec2 scale(0.125f, 0.125f);
	GuiTexture *gui = new GuiTexture(loader.loadTexture("socuwan"), position, scale);
	guis.push_back(gui);
	glm::vec2 position2(0.5f, 0.6f);
	glm::vec2 scale2(0.2f, 0.2f);
	GuiTexture *gui2 = new GuiTexture(loader.loadTexture("thinmatrix"), position2, scale2);
	guis.push_back(gui2);
	glm::vec2 position3(0.8f, 0.9f);
	glm::vec2 scale3(0.2f, 0.2f);
	GuiTexture *gui3 = new GuiTexture(loader.loadTexture("health"), position3, scale3);
	guis.push_back(gui3);

	GuiRenderer guiRenderer(loader);

	MasterRenderer renderer(loader);

	// Water Renderer
	WaterFrameBuffers fbos(display);
	WaterShader waterShader;
	WaterRenderer waterRenderer(loader, waterShader, renderer.getProjectionMatrix(), fbos);
	vector<WaterTile*> waters;
	waters.push_back(new WaterTile(0, 0, 0));
	waters.push_back(new WaterTile(0, 100, 0));
	waters.push_back(new WaterTile(100, 0, 0));
	waters.push_back(new WaterTile(200, 0, 0));
	//waters.push_back(new WaterTile(200, 0, 0));

	glm::vec2 refrGuiPosition(0.75f, -0.75f);
	glm::vec2 refrGuiScale(0.25f, 0.25f);
	GuiTexture *refrGui = new GuiTexture(fbos.getRefractionTexture(), refrGuiPosition, refrGuiScale);
	guis.push_back(refrGui);

	glm::vec2 reflGuiPosition(-0.75f, -0.75f);
	glm::vec2 reflGuiScale(0.25f, 0.25f);
	GuiTexture *reflGui = new GuiTexture(fbos.getReflectionTexture(), reflGuiPosition, reflGuiScale);
	guis.push_back(reflGui);

	glm::vec4 reflClipPlane(0, 1, 0, -waters[0]->getHeight());
	glm::vec4 refrClipPlane(0, -1, 0, waters[0]->getHeight());
	glm::vec4 screenClipPlane(0, -1, 0, 100000);

	while (!isCloseRequested) {
		checkEvents(keyboard, mouse, display);
		//TODO: pass the correct terrain to move()
		player.move(keyboard, display, terrain4);
		camera.move(keyboard, mouse);

		glEnable(GL_CLIP_DISTANCE0);

		//render reflection texture
		fbos.bindReflectionFrameBuffer();
		GLfloat distance = 2 * (camera.getPosition().y - waters[0]->getHeight());
		camera.getPosition().y -= distance;
		camera.invertPitch();
		renderer.renderScene(entities, terrains, lights, camera, reflClipPlane, player, pausing, &stallTexturedModel);
		camera.getPosition().y += distance;
		camera.invertPitch();

		//render refraction texture
		fbos.bindRefractionFrameBuffer();
		renderer.renderScene(entities, terrains, lights, camera, refrClipPlane, player, pausing, &stallTexturedModel);

		//render to screen
		glDisable(GL_CLIP_DISTANCE0);
		fbos.unbindCurrentFrameBuffer();
		renderer.renderScene(entities, terrains, lights, camera, screenClipPlane, player, pausing, &stallTexturedModel);
		waterRenderer.render(waters, camera, display);
		guiRenderer.render(guis);
		display.updateDisplay();
	}

	fbos.cleanUp();
	waterShader.cleanUp();
	guiRenderer.cleanUp();
	renderer.cleanUp();
	loader.cleanUp();
	display.closeDisplay();

	return 0;
}
