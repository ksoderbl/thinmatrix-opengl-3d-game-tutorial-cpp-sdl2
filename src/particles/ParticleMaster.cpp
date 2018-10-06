#include "ParticleMaster.h"
#include "../Player.h"
#include "../Maths.h"
#include "../renderEngine/DisplayManager.h"

ParticleMaster particleMaster;

ParticleMaster::ParticleMaster()
{
}

void ParticleMaster::init(Loader& loader, glm::mat4& projectionMatrix)
{
	renderer = new ParticleRenderer(loader, projectionMatrix);
}

void ParticleMaster::update()
{
	auto it = particles.begin();
	while (it != particles.end()) {
		Particle& p = *it;
		bool stillAlive = p.update();
		if (!stillAlive) {
			it = particles.erase(it);
		} else {
			it++;
		}
	}
}

void ParticleMaster::renderParticles(Camera& camera)
{
	renderer->render(particles, camera);
}

void ParticleMaster::cleanUp()
{
	renderer->cleanUp();
}

void ParticleMaster::addParticle(Particle particle)
{
	particles.push_back(particle);
}
