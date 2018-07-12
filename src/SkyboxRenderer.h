#ifndef SKYBOXRENDERER_H
#define SKYBOXRENDERER_H

#include "Headers.h"
#include "SkyboxShader.h"
#include "RawModel.h"
#include "Loader.h"
#include "Camera.h"

class SkyboxRenderer {
public:
	SkyboxRenderer(Loader& loader, glm::mat4& projectionMatrix);
	void render(Camera& camera);
private:
	static constexpr GLfloat SIZE = 5000.0f;
	vector<GLfloat> VERTICES = {
		-SIZE, SIZE,-SIZE,
		-SIZE,-SIZE,-SIZE,
		 SIZE,-SIZE,-SIZE,
		 SIZE,-SIZE,-SIZE,
		 SIZE, SIZE,-SIZE,
		-SIZE, SIZE,-SIZE,

		-SIZE,-SIZE, SIZE,
		-SIZE,-SIZE,-SIZE,
		-SIZE, SIZE,-SIZE,
		-SIZE, SIZE,-SIZE,
		-SIZE, SIZE, SIZE,
		-SIZE,-SIZE, SIZE,

		 SIZE,-SIZE,-SIZE,
		 SIZE,-SIZE, SIZE,
		 SIZE, SIZE, SIZE,
		 SIZE, SIZE, SIZE,
		 SIZE, SIZE,-SIZE,
		 SIZE,-SIZE,-SIZE,

		-SIZE,-SIZE, SIZE,
		-SIZE, SIZE, SIZE,
		 SIZE, SIZE, SIZE,
		 SIZE, SIZE, SIZE,
		 SIZE,-SIZE, SIZE,
		-SIZE,-SIZE, SIZE,

		-SIZE, SIZE,-SIZE,
		 SIZE, SIZE,-SIZE,
		 SIZE, SIZE, SIZE,
		 SIZE, SIZE, SIZE,
		-SIZE, SIZE, SIZE,
		-SIZE, SIZE,-SIZE,

		-SIZE,-SIZE,-SIZE,
		-SIZE,-SIZE, SIZE,
		 SIZE,-SIZE,-SIZE,
		 SIZE,-SIZE,-SIZE,
		-SIZE,-SIZE, SIZE,
		 SIZE,-SIZE, SIZE
	};
	
	vector<string> TEXTURE_FILES = {
		"skyRight",
		"skyLeft",
		"skyTop",
		"skyBottom",
		"skyBack",
		"skyFront"
	};

	RawModel* cube;
	GLuint texture;
	SkyboxShader* shader;
};

#endif
