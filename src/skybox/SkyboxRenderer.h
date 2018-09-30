#ifndef SKYBOXRENDERER_H
#define SKYBOXRENDERER_H

#include "../Headers.h"
#include "SkyboxShader.h"
#include "../models/RawModel.h"
#include "../Loader.h"
#include "../Camera.h"

class SkyboxRenderer {
public:
	SkyboxRenderer(Loader& loader, glm::mat4& projectionMatrix);
	void render(Camera& camera, GLfloat r, GLfloat g, GLfloat b);
private:
	void bindTextures();

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
	vector<string> NIGHT_TEXTURE_FILES = {
		"nightRight",
		"nightLeft",
		"nightTop",
		"nightBottom",
		"nightBack",
		"nightFront"
	};

	RawModel* cube;
	GLuint texture;
	GLuint nightTexture;
	SkyboxShader* shader;
	GLfloat myTime = 5000;
};

#endif
