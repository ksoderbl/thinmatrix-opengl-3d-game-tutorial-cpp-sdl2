#
# Generic Makefile to make one OpenGL based executable.
# Use GNU make .
#

SHELL	= /bin/sh

SOURCES = \
	engineTester/MainGameLoop.cpp \
	entities/Camera.cpp \
	entities/Entity.cpp \
	entities/Light.cpp \
	entities/Player.cpp \
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
	input/Keyboard.cpp \
	input/Mouse.cpp \
	guis/GuiRenderer.cpp \
	guis/GuiShader.cpp \
	guis/GuiTexture.cpp \
	models/RawModel.cpp \
	models/TexturedModel.cpp \
	normalMappingRenderer/NormalMappingObjLoader.cpp \
	normalMappingRenderer/NormalMappingRenderer.cpp \
	normalMappingRenderer/NormalMappingShader.cpp \
	objConverter/ModelData.cpp \
	objConverter/OBJFileLoader.cpp \
	objConverter/Vertex.cpp \
	particles/Particle.cpp \
	particles/ParticleMaster.cpp \
	particles/ParticleRenderer.cpp \
	particles/ParticleShader.cpp \
	particles/ParticleSystem.cpp \
	particles/ParticleTexture.cpp \
	renderEngine/DisplayManager.cpp \
	renderEngine/EntityRenderer.cpp \
	renderEngine/Loader.cpp \
	renderEngine/MasterRenderer.cpp \
	shaders/ShaderProgram.cpp \
	shaders/StaticShader.cpp \
	skybox/SkyboxRenderer.cpp \
	skybox/SkyboxShader.cpp \
	terrains/HeightsGenerator.cpp \
	terrains/Terrain.cpp \
	terrains/TerrainRenderer.cpp \
	terrains/TerrainShader.cpp \
	terrains/TerrainTexture.cpp \
	terrains/TerrainTexturePack.cpp \
	textures/ModelTexture.cpp \
	textures/TextureData.cpp \
	toolbox/Maths.cpp \
	toolbox/MousePicker.cpp \
	toolbox/Utils.cpp \
	water/WaterFrameBuffers.cpp \
	water/WaterRenderer.cpp \
	water/WaterShader.cpp \
	water/WaterTile.cpp

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
	-rm -f core \#*\# *~ */*~ *.o */*.o $(TARGET)
