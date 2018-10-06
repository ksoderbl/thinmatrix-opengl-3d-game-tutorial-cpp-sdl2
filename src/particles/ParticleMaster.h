#ifndef PARTICLEMASTER_H
#define PARTICLEMASTER_H

#include "../Headers.h"
#include "../models/RawModel.h"
#include "../renderEngine/Loader.h"
#include "../TextureData.h"
#include "Particle.h"
#include "ParticleRenderer.h"
#include "../Camera.h"

class ParticleMaster {
public:
	ParticleMaster();
	void init(Loader& loader, glm::mat4& projectionMatrix);
	void update();
	void renderParticles(Camera& camera);
	void cleanUp();
	void addParticle(Particle particle);
private:
	vector<Particle> particles;
	ParticleRenderer* renderer;
};

extern ParticleMaster particleMaster;

#endif
