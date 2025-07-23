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
	Camera.cpp \
	DisplayManager.cpp \
	Entity.cpp \
	EntityRenderer.cpp \
	guis/GuiRenderer.cpp \
	guis/GuiShader.cpp \
	guis/GuiTexture.cpp \
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
	normalMappingRenderer/NormalMappedObjLoader.cpp \
	normalMappingRenderer/NormalMappingRenderer.cpp \
	normalMappingRenderer/NormalMappingShader.cpp \
	OBJFileLoader.cpp \
	Player.cpp \
	RawModel.cpp \
	ShaderProgram.cpp \
	skybox/SkyboxRenderer.cpp \
	skybox/SkyboxShader.cpp \
	StaticShader.cpp \
	Terrain.cpp \
	TerrainRenderer.cpp \
	TerrainShader.cpp \
	TerrainTexture.cpp \
	TerrainTexturePack.cpp \
	TextureData.cpp \
	TexturedModel.cpp \
	Vertex.cpp \
	water/WaterFrameBuffers.cpp \
	water/WaterRenderer.cpp \
	water/WaterShader.cpp \
	water/WaterTile.cpp



TARGET  = tutorial32
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
