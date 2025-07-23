#include "MasterRenderer.h"

MasterRenderer::MasterRenderer(Loader& loader, DisplayManager& display)
{
	enableCulling();
	createProjectionMatrix(display);
	shader = new StaticShader();
	renderer = new EntityRenderer(*shader, projectionMatrix);
	entitiesMap = new std::map<TexturedModel*, vector<Entity*>*>;
	terrainShader = new TerrainShader();
	terrainRenderer = new TerrainRenderer(*terrainShader, projectionMatrix);
	terrains = new vector<Terrain*>;
	skyboxRenderer = new SkyboxRenderer(loader, projectionMatrix);
}

MasterRenderer::~MasterRenderer()
{
	delete entitiesMap;
	delete renderer;
	delete shader;
	delete terrains;
	delete terrainRenderer;
	delete terrainShader;
	delete skyboxRenderer;
}

void MasterRenderer::renderScene(
	vector<Entity*>& entities,
	vector<Terrain*>& terrains,
	vector<Light*>&lights,
	Camera& camera,
	glm::vec4& clipPlane,
	Player& player,
	bool pausing,
	TexturedModel* stallTexturedModel,
	DisplayManager& display)
{
	processEntity(player);

	for (Terrain* terrain : terrains) {
		processTerrain(*terrain);
	}

	for (Entity* entity : entities) {
		if (!pausing) {
			if (&(entity->getModel()) == stallTexturedModel) {
				entity->increasePosition(0.0, -0.5, 0.0);
				glm::vec3& pos = entity->getPosition();
				if (pos.y < 0)
					entity->increasePosition(0.0, 250, 0.0);
				entity->increaseRotation(1.2, 0.8, 0.7);
			}
		}
		processEntity(*entity);
	}

	render(lights, camera, clipPlane, display);
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
}

void MasterRenderer::render(
	vector<Light*>& lights,
	Camera& camera,
	glm::vec4& clipPlane,
	DisplayManager& display)
{
	prepare();
	shader->start();
	shader->loadClipPlane(clipPlane);
	shader->loadSkyColor(SKY_RED, SKY_GREEN, SKY_BLUE);
	shader->loadLights(lights);
	shader->loadViewMatrix(camera);
	renderer->render(entitiesMap);
	shader->stop();
	terrainShader->start();
	terrainShader->loadClipPlane(clipPlane);
	terrainShader->loadSkyColor(SKY_RED, SKY_GREEN, SKY_BLUE);
	terrainShader->loadLights(lights);
	terrainShader->loadViewMatrix(camera);
	terrainRenderer->render(terrains);
	terrainShader->stop();
	skyboxRenderer->render(camera, SKY_RED, SKY_GREEN, SKY_BLUE, display);
	entitiesMap->clear();
	terrains->clear();
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

void MasterRenderer::prepare()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(SKY_RED, SKY_GREEN, SKY_BLUE, 1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void MasterRenderer::createProjectionMatrix(DisplayManager& display)
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
