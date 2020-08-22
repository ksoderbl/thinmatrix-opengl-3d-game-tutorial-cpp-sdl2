#include "TexturedModel.h"

TexturedModel::TexturedModel(RawModel *model, ModelTexture *texture)
{
	this->rawModel = model;
	this->texture = texture;
}
