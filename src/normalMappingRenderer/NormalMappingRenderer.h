#ifndef NORMALMAPPINGRENDERER_H
#define NORMALMAPPINGRENDERER_H

#include "../Headers.h"
#include "../TexturedModel.h"
#include "../Entity.h"
#include "NormalMappingShader.h"

class NormalMappingRenderer {
public:
	NormalMappingRenderer(glm::mat4& projectionMatrix);
	void render(
		std::map<TexturedModel*, vector<Entity*>*>* entities,
		glm::vec4& clipPlane,
		vector<Light*>&lights,
		Camera& camera);
	void cleanUp();
	void prepareTexturedModel(TexturedModel &model);
	void unbindTexturedModel();
	void prepareInstance(Entity &entity);
	void prepare(glm::vec4& clipPlane, vector<Light*>&lights, Camera& camera);
private:
	NormalMappingShader shader;
};

#endif
