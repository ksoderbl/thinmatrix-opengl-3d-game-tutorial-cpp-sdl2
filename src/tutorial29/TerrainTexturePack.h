#ifndef TERRAINTEXTUREPACK_H
#define TERRAINTEXTUREPACK_H

#include "Headers.h"
#include "TerrainTexture.h"

class TerrainTexturePack {
public:
	TerrainTexturePack(
		TerrainTexture& backgroundTexture,
		TerrainTexture& rTexture,
		TerrainTexture& gTexture,
		TerrainTexture& bTexture);
		
	TerrainTexture& getBackgroundTexture() {
		return backgroundTexture;
	}
	
	TerrainTexture& getrTexture() {
		return rTexture;
	}
	
	TerrainTexture& getgTexture() {
		return gTexture;
	}
	
	TerrainTexture& getbTexture() {
		return bTexture;
	}
private:
	TerrainTexture& backgroundTexture;
	TerrainTexture& rTexture;
	TerrainTexture& gTexture;
	TerrainTexture& bTexture;
};

#endif
