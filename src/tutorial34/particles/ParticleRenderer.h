#ifndef PARTICLERENDERER_H
#define PARTICLERENDERER_H

#include "../Headers.h"
#include "../models/TexturedModel.h"
#include "../Loader.h"
#include "../Entity.h"
#include "../Camera.h"
#include "ParticleShader.h"
#include "Particle.h"

class ParticleRenderer {
public:
	ParticleRenderer(Loader& loader, glm::mat4& projectionMatrix);
	void render(vector<Particle>& particles, Camera& camera);
	void cleanUp();
	void updateModelViewMatrix(glm::vec3& position, GLfloat rotation, GLfloat scale, glm::mat4& viewMatrix);
	void prepare();
	void finishRendering();
	
	void bindTextures(Particle& particle);
	void loadModelMatrix(Particle& particle);
	void unbindTexturedModel();
private:
	RawModel* quad;
	ParticleShader* shader;
};

#endif
