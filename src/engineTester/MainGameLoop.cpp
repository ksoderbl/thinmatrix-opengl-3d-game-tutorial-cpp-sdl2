#include "../renderEngine/DisplayManager.h"
#include "../models/RawModel.h"
#include "../renderEngine/Loader.h"
#include "../renderEngine/EntityRenderer.h"
#include "../shaders/StaticShader.h"
#include "../textures/ModelTexture.h"
#include "../models/TexturedModel.h"
#include "../input/Keyboard.h"
#include "../objConverter/OBJFileLoader.h"
#include "../normalMappingRenderer/NormalMappingObjLoader.h"
#include "../renderEngine/MasterRenderer.h"
#include "../terrains/TerrainTexture.h"
#include "../terrains/TerrainTexturePack.h"
#include "../entities/Player.h"
#include "../input/Mouse.h"
#include "../toolbox/MousePicker.h"
#include "../guis/GuiTexture.h"
#include "../guis/GuiRenderer.h"
#include "../water/WaterRenderer.h"
#include "../water/WaterShader.h"
#include "../water/WaterTile.h"
#include "../water/WaterFrameBuffers.h"
#include "../fontRendering/TextMaster.h"
#include "../fontRendering/FontType.h"
#include "../fontRendering/GUIText.h"
#include "../particles/ParticleMaster.h"
#include "../particles/ParticleSystem.h"
#include "../particles/ParticleTexture.h"
#include "../toolbox/Utils.h"

static bool pausing = false;
static bool isCloseRequested = false;

/* ---------------------------------------------------------------------- */

static void handle_keydown(SDL_KeyboardEvent key)
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

static void handle_keyup(SDL_KeyboardEvent key)
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


void checkEvents()
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

		else if (event.type == SDL_KEYUP)
		{
			handle_keyup(event.key);
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

			int x = event.motion.x;
			int y = event.motion.y;
			//cout << "Mouse pos: (" << x << ", " << y << ")" << endl;
			mouse.setPosition(x, y);
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



int main(int argc, char *argv[])
{
	display.createDisplay();
	srand(676452);

	Loader loader;
	textMaster.init(&loader);

	masterRenderer.init(loader);
	particleMaster.init(loader, masterRenderer.getProjectionMatrix());

	string sampleText0 =

	"void TextMaster::loadText(GUIText* text)"
	"{"
    "    FontType* font = text->getFont();"
    "    TextMeshData* data = font->loadText(text);"
    "    GLuint vao = loader->loadToVAO(data->getVertexPositions(), data->getTextureCoords());"
    "    text->setMeshInfo(vao, data->getVertexCount());"
    "    vector<GUIText*>* textBatch = nullptr;"
    "    map<FontType*, vector<GUIText*>*>::iterator it = texts->find(font);"
    "    if (it == texts->end()) {"
    "            textBatch = new vector<GUIText*>;"
    "            texts->insert(std::pair<FontType*, vector<GUIText*>*>(font, textBatch));"
    "    } else {"
    "            textBatch = it->second;"
    "    }"
    "    textBatch->push_back(text);"
	"}";

	string sampleText1 =

	  //"Use w, a, s, d to move, mouse to change the view, y to launch particles and 1 and 2 for water effects.";
	  "Use w, a, s, d to move, mouse to change the view, and 1 and 2 for water effects.";


	string sampleText2 =
		"Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod "
		"tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, "
		"quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo "
		"consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse "
		"cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non "
		"proident, sunt in culpa qui officia deserunt mollit anim id est laborum. ";

	string fontFile = "../res/fonts/candara.fnt";
	FontType font(loader.loadFontTextureAtlas("fonts/candara"), fontFile);
	//string fontFile = "../res/fonts/harrington.fnt";
	//FontType font(loader.loadFontTextureAtlas("fonts/harrington"), fontFile);
	GUIText text(sampleText1, 2.0, &font, glm::vec2(0.0f, 0.1f), 1.0f, true);
	text.setColor(0.6, 0.8, 1.0);

	//string fontFile2 = "../res/fonts/segoe.fnt";
	//FontType font2(loader.loadFontTextureAtlas("fonts/segoe"), fontFile2);

	string fontFile2 = "../res/fonts/ebGaramond12AllSC.fnt";
	FontType font2(loader.loadFontTextureAtlas("fonts/ebGaramond12AllSC"), fontFile2);
	GUIText text2(sampleText2, 3, &font2, glm::vec2(0.0f, 0.2f), 1.0f, true);
	text2.setColor(1.0, 1.0, 1.0);

	//******** TERRAIN TEXTURE STUFF ********

	TerrainTexture backgroundTexture(loader.loadTexture("grassy2")); // was "grassy"
	TerrainTexture rTexture(loader.loadTexture("mud"));  // was "dirt"
	TerrainTexture gTexture(loader.loadTexture("pinkFlowers"));
	TerrainTexture bTexture(loader.loadTexture("path"));
	TerrainTexturePack texturePack(backgroundTexture, rTexture, gTexture, bTexture);
	TerrainTexture blendMap(loader.loadTexture("blendMapLake"));

	//******** LOAD MODELS ******************

	// rocks
	RawModel *rocksRawModel = OBJFileLoader::loadOBJ("rocks", loader);
	ModelTexture rocksModelTexture = ModelTexture(loader.loadTexture("rocks"));
	TexturedModel rocksTexturedModel = TexturedModel(*rocksRawModel, rocksModelTexture);

	// stall
	//RawModel* stallRawModel = OBJFileLoader::loadOBJ("stall", loader);
	//ModelTexture stallModelTexture = ModelTexture(loader.loadTexture("stallTexture"));
	//TexturedModel stallTexturedModel = TexturedModel(*stallRawModel, stallModelTexture);
	//stallModelTexture.setShineDamper(10);
	//stallModelTexture.setReflectivity(1);

	// pine, was tree
	RawModel* pineRawModel = OBJFileLoader::loadOBJ("pine", loader);
	ModelTexture pineModelTexture = ModelTexture(loader.loadTexture("pine"));
	TexturedModel pineTexturedModel = TexturedModel(*pineRawModel, pineModelTexture);
	pineModelTexture.setShineDamper(4);
	pineModelTexture.setReflectivity(0.3);

	// low poly tree
	//RawModel* lowPolyTreeRawModel = OBJFileLoader::loadOBJ("lowPolyTree", loader);
	//ModelTexture lowPolyTreeModelTexture = ModelTexture(loader.loadTexture("lowPolyTree"));
	//TexturedModel lowPolyTreeTexturedModel = TexturedModel(*lowPolyTreeRawModel, lowPolyTreeModelTexture);
	//lowPolyTreeModelTexture.setShineDamper(4);
	//lowPolyTreeModelTexture.setReflectivity(0.3);

	// bobble tree
	//RawModel* bobbleTreeRawModel = OBJFileLoader::loadOBJ("bobbleTree", loader);
	//ModelTexture bobbleTreeModelTexture = ModelTexture(loader.loadTexture("bobbleTree"));
	//TexturedModel bobbleTreeTexturedModel = TexturedModel(*bobbleTreeRawModel, bobbleTreeModelTexture);
	//bobbleTreeModelTexture.setShineDamper(4);
	//bobbleTreeModelTexture.setReflectivity(0.3);

	// grass
	RawModel* grassRawModel = OBJFileLoader::loadOBJ("grassModel", loader);
	ModelTexture grassModelTexture = ModelTexture(loader.loadTexture("grassTexture"));
	TexturedModel grassTexturedModel = TexturedModel(*grassRawModel, grassModelTexture);
	grassTexturedModel.getTexture().setHasTransparency(true);
	grassTexturedModel.getTexture().setUseFakeLighting(true);
	grassModelTexture.setShineDamper(1);
	grassModelTexture.setReflectivity(0.5);

	// fern
	RawModel* fernRawModel = OBJFileLoader::loadOBJ("fern", loader);
	ModelTexture fernTextureAtlas = ModelTexture(loader.loadTexture("fern"));
	fernTextureAtlas.setShineDamper(4);
	fernTextureAtlas.setReflectivity(0.1);
	fernTextureAtlas.setNumberOfRows(2);
	TexturedModel fernTexturedModel = TexturedModel(*fernRawModel, fernTextureAtlas);
	fernTexturedModel.getTexture().setHasTransparency(true);
	fernTexturedModel.getTexture().setUseFakeLighting(true);

	// flower, using fern as raw model, seems to work
	RawModel* flowerRawModel = OBJFileLoader::loadOBJ("fern", loader);
	ModelTexture flowerTextureAtlas = ModelTexture(loader.loadTexture("diffuse"));
	flowerTextureAtlas.setShineDamper(5);
	flowerTextureAtlas.setReflectivity(0.2);
	flowerTextureAtlas.setNumberOfRows(2);
	TexturedModel flowerTexturedModel = TexturedModel(*flowerRawModel, flowerTextureAtlas);
	flowerTexturedModel.getTexture().setHasTransparency(true);
	flowerTexturedModel.getTexture().setUseFakeLighting(true);

	// toon rocks
	//RawModel* toonRocksRawModel = OBJFileLoader::loadOBJ("toonRocks", loader);
	//ModelTexture toonRocksModelTexture = ModelTexture(loader.loadTexture("toonRocks"));
	//TexturedModel toonRocksTexturedModel = TexturedModel(*toonRocksRawModel, toonRocksModelTexture);

	vector<Terrain*> terrains;
	Terrain terrain(0, -1, loader, texturePack, blendMap, "heightMapLake");
	//Terrain terrain2(-1, 0, loader, texturePack, blendMap, "heightmap");
	//Terrain terrain3(-1, -1, loader, texturePack, blendMap, "heightmap");
	//Terrain terrain4(0, -1, loader, texturePack, blendMap, "heightmap");
	terrains.push_back(&terrain);
	//terrains.push_back(&terrain2);
	//terrains.push_back(&terrain3);
	//terrains.push_back(&terrain4);

	vector<Entity*> entities;
	vector<Entity*> normalMapEntities;

	//******************NORMAL MAP MODELS************************

	// barrel
	//TexturedModel barrelModel = new TexturedModel(NormalMappingObjLoader.loadOBJ("barrel", loader),
	//new ModelTexture(loader.loadTexture("barrel")));

	RawModel* barrelRawModel = NormalMappingObjLoader::loadOBJ("barrel", loader);
	ModelTexture barrelModelTexture = ModelTexture(loader.loadTexture("barrel"));
	TexturedModel barrelModel = TexturedModel(*barrelRawModel, barrelModelTexture);
	barrelModel.getTexture().setNormalMap(loader.loadTexture("barrelNormal"));
	barrelModel.getTexture().setShineDamper(10);
	barrelModel.getTexture().setReflectivity(0.5f);

	// crate
	//TexturedModel crateModel = new TexturedModel(NormalMappingObjLoader.loadOBJ("crate", loader),
	//new ModelTexture(loader.loadTexture("crate")));

	RawModel* crateRawModel = NormalMappingObjLoader::loadOBJ("crate", loader);
	ModelTexture crateModelTexture = ModelTexture(loader.loadTexture("crate"));
	TexturedModel crateModel = TexturedModel(*crateRawModel, crateModelTexture);
	crateModel.getTexture().setNormalMap(loader.loadTexture("crateNormal"));
	crateModel.getTexture().setShineDamper(10);
	crateModel.getTexture().setReflectivity(0.5f);

	// boulder
	//TexturedModel boulderModel = new TexturedModel(NormalMappingObjLoader.loadOBJ("boulder", loader),
	//new ModelTexture(loader.loadTexture("boulder")));

	RawModel* boulderRawModel = NormalMappingObjLoader::loadOBJ("boulder", loader);
	ModelTexture boulderModelTexture = ModelTexture(loader.loadTexture("boulder"));
	TexturedModel boulderModel = TexturedModel(*boulderRawModel, boulderModelTexture);
	boulderModel.getTexture().setNormalMap(loader.loadTexture("boulderNormal"));
	boulderModel.getTexture().setShineDamper(10);
	boulderModel.getTexture().setReflectivity(0.5f);

	// football
	//RawModel* footRawModel = NormalMappingObjLoader::loadOBJ("foot", loader);
	//ModelTexture footModelTexture = ModelTexture(loader.loadTexture("foot"));
	//TexturedModel footModel = TexturedModel(*footRawModel, footModelTexture);
	//footModel.getTexture().setNormalMap(loader.loadTexture("footNormal"));
	//footModel.getTexture().setShineDamper(10);
	//footModel.getTexture().setReflectivity(0.5f);

	//************ENTITIES*******************

	Entity entity(barrelModel, glm::vec3(Terrain::SIZE/2, 0, -Terrain::SIZE/2), 0, 0, 0, 1.0f);
	//Entity entity2(boulderModel, glm::vec3(Terrain::SIZE/2 + 20, 0, -Terrain::SIZE/2), 0, 0, 0, 1.0f);
	Entity entity3(crateModel, glm::vec3(Terrain::SIZE/2 -20, 0, -Terrain::SIZE/2), 0, 0, 0, 0.04f);
	//Entity entity4(footModel, glm::vec3(Terrain::SIZE/2, 0, -Terrain::SIZE/2 + 20), 0, 0, 0, 2.0f);
	normalMapEntities.push_back(&entity);
	//normalMapEntities.push_back(&entity2);
	normalMapEntities.push_back(&entity3);
	//normalMapEntities.push_back(&entity4);

	GLfloat limit1 = Terrain::SIZE / 4;
	GLfloat limit2 = Terrain::SIZE - limit1;

	for (int i = 0; i < 2*240; i++) {
		if (i % 4 == 0) {
			GLfloat x = Utils::Rand() * Terrain::SIZE;
			GLfloat z = Utils::Rand() * -Terrain::SIZE;
			GLfloat y = terrain.getHeightOfTerrain(x, z);
			{
				normalMapEntities.push_back(
					new Entity(boulderModel, glm::vec3(x, y, z), 
						   Utils::Rand() * 360, Utils::Rand() * 360,  Utils::Rand() * 360,
						   Utils::Rand() * 0.9f + 0.1f));
			}
		}
		if (i % 3 == 0) {
			GLfloat x = Utils::Rand() * Terrain::SIZE;
			GLfloat z = Utils::Rand() * -Terrain::SIZE;
			if ((x > limit1 && x < limit2) && (z < -limit1 && z > -limit2)) {
			} else {
				GLfloat y = terrain.getHeightOfTerrain(x, z);
				entities.push_back(
					new Entity(fernTexturedModel, Utils::RandInt(4), glm::vec3(x, y, z), 
						   0, Utils::Rand() * 360, 0, 0.9f));
			}
		}
		if (i % 2 == 0) {
			GLfloat x = Utils::Rand() * Terrain::SIZE;
			GLfloat z = Utils::Rand() * -Terrain::SIZE;
			if ((x > limit1 && x < limit2) && (z < -limit1 && z > -limit2)) {
			} else {
				GLfloat y = terrain.getHeightOfTerrain(x, z);
				entities.push_back(
					new Entity(pineTexturedModel, glm::vec3(x, y, z),
						   0, Utils::Rand() * 360, 0, Utils::Rand() * 0.6f + 0.8f));
			}
		}
	}

	Entity rocks(rocksTexturedModel, glm::vec3(Terrain::SIZE/2, 2*4.6f, -Terrain::SIZE/2),
		     0, 0, 0, Terrain::SIZE/2);
	entities.push_back(&rocks);

	//*******************OTHER SETUP***************

	vector<Light*> lights;
	Light sun = Light(glm::vec3(10000, 10000, -10000), glm::vec3(1.3f, 1.3f, 1.3f));
	//Light light2 = Light(glm::vec3(0, 20, 0), glm::vec3(2, 0, 0), glm::vec3(1, 0.01f, 0.002f));
	//Light light3 = Light(glm::vec3(0, 20, -Terrain::SIZE), glm::vec3(0, 2, 2), glm::vec3(1, 0.01f, 0.002f));
	//Light light4 = Light(glm::vec3(Terrain::SIZE, 20, 0),  glm::vec3(2, 2, 0), glm::vec3(1, 0.01f, 0.002f));
	lights.push_back(&sun);
	//lights.push_back(&light2);
	//lights.push_back(&light3);
	//lights.push_back(&light4);

	//RawModel* lampRawModel = OBJFileLoader::loadOBJ("lamp", loader);
	//ModelTexture lampModelTexture = ModelTexture(loader.loadTexture("lamp"));
	//TexturedModel lampModel = TexturedModel(*lampRawModel, lampModelTexture);
	//lampModel.getTexture().setUseFakeLighting(true);

	//entities.push_back(new Entity(lampModel, glm::vec3(0, 5, 0), 0, 0, 0, 1));
	//entities.push_back(new Entity(lampModel, glm::vec3(0, 5, -Terrain::SIZE), 0, 0, 0, 1));
	//entities.push_back(new Entity(lampModel, glm::vec3(Terrain::SIZE, 5, 0), 0, 0, 0, 1));

	RawModel* playerRawModel = OBJFileLoader::loadOBJ("person", loader);
	ModelTexture playerModelTexture = ModelTexture(loader.loadTexture("playerTexture"));
	TexturedModel playerTexturedModel = TexturedModel(*playerRawModel, playerModelTexture);
	playerModelTexture.setShineDamper(10);
	playerModelTexture.setReflectivity(1);

	//Player player(playerTexturedModel, glm::vec3(Terrain::SIZE/2, 5, -Terrain::SIZE/2), 0, 0, 0, 0.6f);
	Player player(playerTexturedModel, glm::vec3(Terrain::SIZE/5, 5, -Terrain::SIZE/5), 0, 100, 0, 0.6f);
	entities.push_back(&player);

	Camera camera(player);

	vector<GuiTexture*> guis;
	//glm::vec2 position(0.7f, 0.5f);
	//glm::vec2 scale(0.125f, 0.125f);
	//GuiTexture *gui = new GuiTexture(loader.loadTexture("socuwan"), position, scale);

	//glm::vec2 position2(0.5f, 0.6f);
	//glm::vec2 scale2(0.2f, 0.2f);
	//GuiTexture *gui2 = new GuiTexture(loader.loadTexture("thinmatrix"), position2, scale2);

	glm::vec2 position3(0.8f, 0.9f);
	glm::vec2 scale3(0.2f, 0.2f);
	GuiTexture *gui3 = new GuiTexture(loader.loadTexture("health"), position3, scale3);

	//guis.push_back(gui);
	//guis.push_back(gui2);
	guis.push_back(gui3);

	GuiRenderer guiRenderer(loader);

	MousePicker picker(camera, masterRenderer.getProjectionMatrix(), &terrain);
	//Entity *lampEntity = new Entity(lampModel, glm::vec3(0, 0, 0), 0, 0, 0, 1);
	//entities.push_back(lampEntity);
	//Light light = Light(glm::vec3(0, 14, 0), glm::vec3(3, 3, 0), glm::vec3(1, 0.01f, 0.002f));
	//lights.push_back(&light);

	//**********Water Renderer Set-up************************

	WaterFrameBuffers buffers;
	WaterShader waterShader;
	WaterRenderer waterRenderer(loader, waterShader, masterRenderer.getProjectionMatrix(),
				    masterRenderer.getNearPlane(), masterRenderer.getFarPlane(), buffers);
	vector<WaterTile*> waters;

	/*
	int maxWaterIndex = 3;
	for (int j = -maxWaterIndex; j <= maxWaterIndex; j++) {
		for (int i = -maxWaterIndex; i <= maxWaterIndex; i++) {
			WaterTile* water = new WaterTile(
				Terrain::SIZE / 2 + i * WaterTile::TILE_SIZE,
				Terrain::SIZE / 2 + j * WaterTile::TILE_SIZE,
				2.0f);
			waters.push_back(water);
		}
	}
	WaterTile* water = waters[0];
	*/
	WaterTile* water = new WaterTile(Terrain::SIZE / 2, -Terrain::SIZE / 2, 0);
	waters.push_back(water);

	glm::vec2 refrGuiPosition(-0.7f, -0.9f);
	glm::vec2 refrGuiScale(0.1f, 0.1f);
	GuiTexture *refrGui = new GuiTexture(buffers.getRefractionTexture(), refrGuiPosition, refrGuiScale);
	guis.push_back(refrGui);

	glm::vec2 reflGuiPosition(-0.9f, -0.9f);
	glm::vec2 reflGuiScale(0.1f, 0.1f);
	GuiTexture *reflGui = new GuiTexture(buffers.getReflectionTexture(), reflGuiPosition, reflGuiScale);
	guis.push_back(reflGui);

	glm::vec4 reflClipPlane(0, 1, 0, -water->getHeight() + 0.5f);
	glm::vec4 refrClipPlane(0, -1, 0, water->getHeight() + 0.5f);
	glm::vec4 screenClipPlane(0, -1, 0, 1000000);


	ParticleTexture particleStarTexture(loader.loadTexture("particleStar"), 1, true);
	ParticleTexture particleAtlasTexture(loader.loadTexture("particleAtlas"), 4, true);
	ParticleTexture particleCosmicTexture(loader.loadTexture("cosmic"), 4, true);
	ParticleTexture particleSmokeTexture(loader.loadTexture("smoke"), 8, false);
	ParticleTexture particleFireTexture(loader.loadTexture("fire"), 8, true);


	ParticleSystem fireSystem(particleAtlasTexture, 50, 4, -0.01, 1.2, 5);
	fireSystem.randomizeRotation();
	fireSystem.setDirection(glm::vec3(0, 1, 0), 0.2f);
	fireSystem.setLifeError(0.5f);
	fireSystem.setSpeedError(0.5f);
	fireSystem.setScaleError(0.5f);

	ParticleSystem smokeSystem(particleSmokeTexture, 50, 1, -0.01f, 5, 8.0f);
	smokeSystem.setDirection(glm::vec3(0, 1, 0), 1.0f);
	smokeSystem.setLifeError(3.1f);
	smokeSystem.setSpeedError(1.25f);
	smokeSystem.setScaleError(2.5f);
	smokeSystem.randomizeRotation();

	ParticleSystem starSystem(particleStarTexture, 100, 20, 0.8f, 7, 2);
	starSystem.setDirection(glm::vec3(0, 1, 0), 0.3f);
	starSystem.setLifeError(0.1f);
	starSystem.setSpeedError(0.25f);
	starSystem.setScaleError(0.5f);
	starSystem.randomizeRotation();

	ParticleSystem cosmicSystem(particleCosmicTexture, 50, 50, 0.3f, 3, 5);
	cosmicSystem.setDirection(glm::vec3(0, 1, 0), 0.8f);
	cosmicSystem.setLifeError(0.1f);
	cosmicSystem.setSpeedError(0.25f);
	cosmicSystem.setScaleError(0.5f);
	cosmicSystem.randomizeRotation();

	ParticleSystem atlasSystem(particleAtlasTexture, 50, 50, 0.4f, 6, 4);
	atlasSystem.setDirection(glm::vec3(0, 1, 0), 0.6f);
	atlasSystem.setLifeError(0.2f);
	atlasSystem.setSpeedError(0.5f);
	atlasSystem.setScaleError(0.25f);
	atlasSystem.randomizeRotation();


	//****************Game Loop Below*********************

	int loops = 0;

	//string fontFile3 = "../res/fonts/ebGaramond12AllSC.fnt";
	//FontType font3(loader.loadFontTextureAtlas("fonts/ebGaramond12AllSC"), fontFile3);
	//uint64_t prevUs = 0;

	while (!isCloseRequested) {
		checkEvents();
		//TODO: pass the correct terrain to move()
		player.move(terrain, water);
		camera.move();
		/*picker.update();
		glm::vec3* terrainPoint = picker.getCurrentTerrainPoint();
		if (terrainPoint != nullptr) {
			glm::vec3 pt = *terrainPoint;
			lampEntity->setPosition(pt);
			light.setPosition(glm::vec3(pt.x, pt.y + 14, pt.z));
		}
		*/
		//if (keyboard.isKeyDown(SDLK_y)) {
		//	glm::vec3 velocity(0, 50, 0);
		//	Particle particle(player.getPosition(), velocity, 1, 2.5, 0, 1);
		//}
		//smokeSystem.generateParticles(player.getPosition() + glm::vec3(0, 5, 0));
		//fireSystem.generateParticles(player.getPosition() + glm::vec3(0, 5, 0));
		smokeSystem.generateParticles(glm::vec3(290.0f, 10.0f, -330.0f));
		fireSystem.generateParticles(glm::vec3(350.0f, 10.0f, -300.0f));
		starSystem.generateParticles(glm::vec3(300.0f, 20.0f, -400.0f));
		cosmicSystem.generateParticles(glm::vec3(420.0f, 10.0f, -270.0f));
		atlasSystem.generateParticles(glm::vec3(420.0f, 10.0f, -270.0f));

		particleMaster.update(camera);

		entity.increaseRotation(0.0f, 1.1f, 0.0f);
		//entity2.increaseRotation(0.0f, 1.2f, 0.0f);
		entity3.increaseRotation(0.0f, 1.3f, 0.0f);
		//entity4.increaseRotation(0.4f, 1.4f, 0.9f);

		//render reflection texture
		buffers.bindReflectionFrameBuffer();
		GLfloat distance = 2 * (camera.getPosition().y - waters[0]->getHeight());
		camera.getPosition().y -= distance;
		camera.invertPitch();
		masterRenderer.renderScene(entities, normalMapEntities, terrains, lights, camera,
				     reflClipPlane, true);
		camera.getPosition().y += distance;
		camera.invertPitch();

		//render refraction texture
		buffers.bindRefractionFrameBuffer();
		masterRenderer.renderScene(entities, normalMapEntities, terrains, lights, camera,
				     refrClipPlane, true);
		//render to screen
		buffers.unbindCurrentFrameBuffer();

		masterRenderer.renderScene(entities, normalMapEntities, terrains, lights, camera,
				     screenClipPlane, false);
		waterRenderer.render(waters, camera, sun);

		// after 3d stuff, before the 2d stuff
		particleMaster.renderParticles(camera);

		guiRenderer.render(guis);
		textMaster.render();

		display.updateDisplay();
		loops++;

		if (loops > 100) {
			textMaster.removeText(&text);
			textMaster.removeText(&text2);
		}


		//uint64_t us = Utils::GetMicroSeconds();
		//
		//if (prevUs != 0) {
		//	cout << "Delta: " << us - prevUs << endl;
		//}
		//prevUs = us;

		//stringstream ss;
		//ss << us;
		//GUIText text3(ss.str(), 4, &font3, glm::vec2(0.1f, 0.1f), 0.5f, false);
		//text3.setColor(1.0, 1.0, 0.0);
	}

	//*********Clean Up Below**************

	particleMaster.cleanUp();
	textMaster.cleanUp();
	buffers.cleanUp();
	waterShader.cleanUp();
	guiRenderer.cleanUp();
	masterRenderer.cleanUp();
	loader.cleanUp();
	display.closeDisplay();

	return 0;
}
