#include "MasterRenderer.h"

MasterRenderer masterRenderer;

MasterRenderer::MasterRenderer()
{
	FOV = 70;
	NEAR_PLANE = 0.1f;
	FAR_PLANE = 10000.0f;
	//RED = 0.5444f;
	//GREEN = 0.62f;
	//BLUE = 0.69f;
	RED = 157.0f / 256;   //0.9444f;
	GREEN = 197.0f / 256; //0.52f;
	BLUE = 213.0f / 256;  //0.79f;
	FOG_DENSITY = 0.0005f;
	FOG_GRADIENT = 1.0f;
}

MasterRenderer::~MasterRenderer()
{
	delete entitiesMap;
	delete normalMapEntitiesMap;
	delete renderer;
	delete shader;
	delete terrains;
	delete terrainRenderer;
	delete terrainShader;
	delete skyboxRenderer;
	delete normalMapRenderer;
}

void MasterRenderer::init(Loader& loader)
{
	enableCulling();
	createProjectionMatrix();
	shader = new StaticShader();
	renderer = new EntityRenderer(*shader, projectionMatrix);
	entitiesMap = new std::map<TexturedModel*, vector<Entity*>*>;
	normalMapEntitiesMap = new std::map<TexturedModel*, vector<Entity*>*>;
	terrainShader = new TerrainShader();
	terrainRenderer = new TerrainRenderer(*terrainShader, projectionMatrix);
	terrains = new vector<Terrain*>;
	skyboxRenderer = new SkyboxRenderer(loader, projectionMatrix);
	normalMapRenderer = new NormalMappingRenderer(projectionMatrix);
}

void MasterRenderer::renderScene(
	vector<Entity*>& entities,
	vector<Entity*>& normalMapEntities,
	vector<Terrain*>& terrains,
	vector<Light*>&lights,
	Camera& camera,
	glm::vec4& clipPlane,
	bool useClipping)
{
	//processEntity(player);

	for (Terrain* terrain : terrains) {
		processTerrain(*terrain);
	}
	for (Entity* entity : entities) {
		processEntity(*entity);
	}
	for (Entity* entity : normalMapEntities) {
		processNormalMapEntity(*entity);
	}

	render(lights, camera, clipPlane, useClipping);
}

void MasterRenderer::enableCulling()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void MasterRenderer::disableCulling()
{
	glDisable(GL_CULL_FACE);
}

void MasterRenderer::cleanUp()
{
	shader->cleanUp();
	terrainShader->cleanUp();
	normalMapRenderer->cleanUp();
}

void MasterRenderer::render(
	vector<Light*>& lights,
	Camera& camera,
	glm::vec4& clipPlane,
	bool useClipping)
{
	prepare();

	if (useClipping) {
		glEnable(GL_CLIP_DISTANCE0);
	} else {
		glDisable(GL_CLIP_DISTANCE0);
	}

	shader->start();
	shader->loadClipPlane(clipPlane);
	shader->loadSkyColor(RED, GREEN, BLUE);
	shader->loadFogVariables(MasterRenderer::FOG_DENSITY, MasterRenderer::FOG_GRADIENT);
	shader->loadLights(lights);
	shader->loadViewMatrix(camera);
	renderer->render(entitiesMap);
	shader->stop();

	normalMapRenderer->render(normalMapEntitiesMap, clipPlane, lights, camera);

	terrainShader->start();
	terrainShader->loadClipPlane(clipPlane);
	terrainShader->loadSkyColor(RED, GREEN, BLUE);
	terrainShader->loadFogVariables(MasterRenderer::FOG_DENSITY, MasterRenderer::FOG_GRADIENT);
	terrainShader->loadLights(lights);
	terrainShader->loadViewMatrix(camera);
	terrainRenderer->render(terrains);
	terrainShader->stop();

	if (useClipping) {
		glDisable(GL_CLIP_DISTANCE0);
	}

	skyboxRenderer->render(camera, RED, GREEN, BLUE);

	terrains->clear();
	entitiesMap->clear();
	normalMapEntitiesMap->clear();
}

void MasterRenderer::processTerrain(Terrain& terrain)
{
	terrains->push_back(&terrain);
}

void MasterRenderer::processEntity(Entity& entity)
{
	TexturedModel& entityModel = entity.getModel();
	std::map<TexturedModel*, vector<Entity*>*>::iterator it;

	it = entitiesMap->find(&entityModel);
  	if (it != entitiesMap->end()) {
  		vector<Entity*>* batch = it->second;
  		batch->push_back(&entity);
  	} else {
  		vector<Entity*>* newBatch = new vector<Entity*>();
  		newBatch->push_back(&entity);
  		entitiesMap->insert(std::make_pair(&entityModel, newBatch));
  	}
}

void MasterRenderer::processNormalMapEntity(Entity& entity)
{
	TexturedModel& entityModel = entity.getModel();
	std::map<TexturedModel*, vector<Entity*>*>::iterator it;

	it = normalMapEntitiesMap->find(&entityModel);
	if (it != normalMapEntitiesMap->end()) {
		vector<Entity*>* batch = it->second;
		batch->push_back(&entity);
	} else {
		vector<Entity*>* newBatch = new vector<Entity*>();
		newBatch->push_back(&entity);
		normalMapEntitiesMap->insert(std::make_pair(&entityModel, newBatch));
	}
}

void MasterRenderer::prepare()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(RED, GREEN, BLUE, 1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void MasterRenderer::createProjectionMatrix()
{
	// https://www.youtube.com/watch?v=50Y9u7K0PZo#t=7m30s
	// https://www.youtube.com/watch?v=50Y9u7K0PZo#t=10m10s
	// http://www.songho.ca/opengl/gl_projectionmatrix.html
	GLfloat aspectRatio = display.getAspectRatio();
	cout << "MasterRenderer::createProjectionMatrix: Width " << display.getWidth() << "\n";
	cout << "MasterRenderer::createProjectionMatrix: Height " << display.getHeight() << "\n";
	cout << "MasterRenderer::createProjectionMatrix: Aspect ratio set to " << aspectRatio << ":1\n";

	GLfloat angle = FOV / 2.0f;
	GLfloat radAngle = glm::radians(angle);
	GLfloat tanAngle = tanf(radAngle);
	GLfloat y_scale = (GLfloat) (1.0f / tanAngle) * aspectRatio;
	GLfloat x_scale = y_scale / aspectRatio;
	GLfloat frustum_length = FAR_PLANE - NEAR_PLANE;

	glm::mat4 m = glm::mat4(1.0f);

	m[0][0] = x_scale;
	m[1][1] = y_scale;
	m[2][2] = -((FAR_PLANE + NEAR_PLANE) / frustum_length);
	m[2][3] = -1;
	m[3][2] = -(2 * NEAR_PLANE * FAR_PLANE) / frustum_length;
	m[3][3] = 0;

	//Maths::printMatrix(m, "proj1");

	//glm::mat4 projectionMatrix2 = glm::perspective(FOV, aspectRatio, NEAR_PLANE, FAR_PLANE);
	//Maths::printMatrix(projectionMatrix2, "proj2");

	projectionMatrix = m;
}

glm::mat4& MasterRenderer::getProjectionMatrix()
{
	return projectionMatrix;
}
