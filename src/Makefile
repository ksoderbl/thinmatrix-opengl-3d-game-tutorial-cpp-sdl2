#
# Generic Makefile to make one OpenGL based executable.
# Use GNU make .
#

SHELL	= /bin/sh

SOURCES = \
	fontRendering/Character.cpp \
	fontRendering/FontRenderer.cpp \
	fontRendering/FontShader.cpp \
	fontRendering/FontType.cpp \
	fontRendering/GUIText.cpp \
	fontRendering/Line.cpp \
	fontRendering/MetaFile.cpp \
	fontRendering/TextMaster.cpp \
	fontRendering/TextMeshCreator.cpp \
	fontRendering/TextMeshData.cpp \
	fontRendering/Word.cpp \
	guis/GuiRenderer.cpp \
	guis/GuiShader.cpp \
	guis/GuiTexture.cpp \
	models/RawModel.cpp \
	models/TexturedModel.cpp \
	normalMappingRenderer/NormalMappingObjLoader.cpp \
	normalMappingRenderer/NormalMappingRenderer.cpp \
	normalMappingRenderer/NormalMappingShader.cpp \
	particles/Particle.cpp \
	particles/ParticleMaster.cpp \
	particles/ParticleRenderer.cpp \
	particles/ParticleShader.cpp \
	particles/ParticleSystem.cpp \
	skybox/SkyboxRenderer.cpp \
	skybox/SkyboxShader.cpp \
	water/WaterFrameBuffers.cpp \
	water/WaterRenderer.cpp \
	water/WaterShader.cpp \
	water/WaterTile.cpp \
	Camera.cpp \
	DisplayManager.cpp \
	Entity.cpp \
	EntityRenderer.cpp \
	Keyboard.cpp \
	Light.cpp \
	Loader.cpp \
	MainGameLoop.cpp \
	MasterRenderer.cpp \
	Maths.cpp \
	ModelData.cpp \
	ModelTexture.cpp \
	Mouse.cpp \
	MousePicker.cpp \
	OBJFileLoader.cpp \
	Player.cpp \
	ShaderProgram.cpp \
	StaticShader.cpp \
	Terrain.cpp \
	TerrainRenderer.cpp \
	TerrainShader.cpp \
	TerrainTexture.cpp \
	TerrainTexturePack.cpp \
	TextureData.cpp \
	Utils.cpp \
	Vertex.cpp



TARGET  = main
OBJECTS = $(SOURCES:.cpp=.o)

CC	= g++
SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)
CFLAGS	= -O2 -Wall $(SDL_CFLAGS)
LDFLAGS	= -lGLEW -lGLU -lGL -lm $(SDL_LDFLAGS) -lpng


all: $(TARGET)
.PHONY: all


$(OBJECTS): %.o: %.cpp
	$(CC) -c $(CFLAGS) $^ -o $@

$(TARGET): $(OBJECTS)
	$(CC) $^ $(LDFLAGS) -o $@

.PHONY: clean
clean:
	-rm -f core \#*\# *~ */*~ $(OBJECTS) $(TARGET)
