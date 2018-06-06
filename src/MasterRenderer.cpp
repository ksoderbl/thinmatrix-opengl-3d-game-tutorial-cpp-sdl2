#include "MasterRenderer.h"

void MasterRenderer::render(Light& sun, Camera& camera)
{
	renderer->prepare();
	shader->start();
	shader->loadLight(sun);
	shader->loadViewMatrix(camera);
	renderer->render(entities);
	shader->stop();
	entities->clear();
}

void MasterRenderer::processEntity(Entity &entity)
{
	TexturedModel& entityModel = entity.getModel();
	std::map<TexturedModel*, vector<Entity*>*>::iterator it;

	it = entities->find(&entityModel);
  	if (it != entities->end()) {
  		vector<Entity*>* batch = it->second;
  		batch->push_back(&entity);
  	} else {
  		vector<Entity*>* newBatch = new vector<Entity*>();
  		newBatch->push_back(&entity);
  		entities->insert(std::make_pair(&entityModel, newBatch));
  	}
}