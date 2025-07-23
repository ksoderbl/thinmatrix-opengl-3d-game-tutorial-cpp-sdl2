// package/namespace models

#ifndef TEXTUREDMODEL_H
#define TEXTUREDMODEL_H

#include "../Headers.h"
#include "RawModel.h"
#include "../ModelTexture.h"

class TexturedModel {
public:
	TexturedModel(RawModel& model, ModelTexture& texture) : rawModel(model), texture(texture) {}
	RawModel& getRawModel() {
		return rawModel;
	}
	ModelTexture& getTexture() {
		return texture;
	}

private:
	RawModel& rawModel;
	ModelTexture& texture;
};

#endif
