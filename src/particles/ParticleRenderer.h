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
	void updateTexCoordInfo(Particle& particle, vector<GLfloat>& vboData);
	void bindTexture(ParticleTexture* texture);
	void updateModelViewMatrix(glm::vec3& position, GLfloat rotation, GLfloat scale, glm::mat4& viewMatrix,
				   vector<GLfloat>& vboData);
	void storeMatrixData(glm::mat4& matrix, vector<GLfloat>& vboData);
	void prepare();
	void finishRendering();
	
	void bindTextures(Particle& particle);
	void loadModelMatrix(Particle& particle);
	void unbindTexturedModel();
private:
	static constexpr int MAX_INSTANCES = 10000;
	static constexpr int INSTANCE_DATA_LENGTH = 21; // 16 (model view matrix) + 4 (texture info) + 1 (blend factor)
	RawModel* quad;
	ParticleShader shader;
	Loader& loader;
	GLuint vboID;
	vector<GLfloat> buffer;
	int pointer; // where in the buffer we are writing
};

#endif
