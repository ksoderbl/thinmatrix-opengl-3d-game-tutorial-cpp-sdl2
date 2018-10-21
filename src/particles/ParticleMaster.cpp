#include "ParticleMaster.h"
#include "../entities/Player.h"
#include "../toolbox/Maths.h"
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
	auto mit = particlesMap.begin();
	while (mit != particlesMap.end()) {
		vector<Particle>& particles = mit->second;
		auto vit = particles.begin();
		while (vit != particles.end()) {
			Particle& p = *vit;
			bool stillAlive = p.update();
			if (!stillAlive) {
				vit = particles.erase(vit);
			} else {
				vit++;
			}
		}
		mit++;
	}
}

void ParticleMaster::renderParticles(Camera& camera)
{
	renderer->render(particlesMap, camera);
}

void ParticleMaster::cleanUp()
{
	renderer->cleanUp();
}

// map<ParticleTexture*, vector<Particle>> particlesMap;
void ParticleMaster::addParticle(Particle particle)
{
	ParticleTexture* texture = particle.getTexture();
	auto it = particlesMap.find(texture);
	if (it != particlesMap.end()) {
		vector<Particle>& particles = it->second;
		particles.push_back(particle);
	}
	else {
		vector<Particle> particles;
		particles.push_back(particle);
		particlesMap.insert(std::make_pair(texture, particles));
	}
}
