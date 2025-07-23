#ifndef PARTICLERENDERER_H
#define PARTICLERENDERER_H

#include "../Headers.h"
#include "../models/TexturedModel.h"
#include "../renderEngine/Loader.h"
#include "../entities/Entity.h"
#include "../entities/Camera.h"
#include "ParticleShader.h"
#include "Particle.h"
#include "ParticleTexture.h"

class ParticleRenderer {
public:
	ParticleRenderer(Loader& loader, glm::mat4& projectionMatrix);
	void render(map<ParticleTexture*, vector<Particle>>& particlesMap, Camera& camera);
	void cleanUp();
	void updateModelViewMatrix(glm::vec3& position, GLfloat rotation, GLfloat scale, glm::mat4& viewMatrix);
	void prepare();
	void finishRendering();
	
	void bindTextures(Particle& particle);
	void loadModelMatrix(Particle& particle);
	void unbindTexturedModel();
private:
	RawModel* quad;
	ParticleShader shader;
};

#endif
