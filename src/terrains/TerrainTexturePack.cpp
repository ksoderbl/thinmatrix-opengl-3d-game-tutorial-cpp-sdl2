#include "TerrainTexturePack.h"

TerrainTexturePack::TerrainTexturePack(
	TerrainTexture& backgroundTexture,
	TerrainTexture& rTexture,
	TerrainTexture& gTexture,
	TerrainTexture& bTexture) : 
		backgroundTexture(backgroundTexture),
		rTexture(rTexture),
		gTexture(gTexture),
		bTexture(bTexture)
{
}
