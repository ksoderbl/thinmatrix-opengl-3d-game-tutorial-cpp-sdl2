#
# Generic Makefile to make one OpenGL based executable.
# Use GNU make .
#

SHELL	= /bin/sh

SOURCES = \
	Camera.cpp \
	DisplayManager.cpp \
	Entity.cpp \
	EntityRenderer.cpp \
	GuiRenderer.cpp \
	GuiShader.cpp \
	GuiTexture.cpp \
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
	NormalMappedObjLoader.cpp \
	NormalMappingRenderer.cpp \
	NormalMappingShader.cpp \
	OBJFileLoader.cpp \
	Player.cpp \
	RawModel.cpp \
	ShaderProgram.cpp \
	SkyboxRenderer.cpp \
	SkyboxShader.cpp \
	StaticShader.cpp \
	Terrain.cpp \
	TerrainRenderer.cpp \
	TerrainShader.cpp \
	TerrainTexture.cpp \
	TerrainTexturePack.cpp \
	TextureData.cpp \
	TexturedModel.cpp \
	Vertex.cpp \
	WaterFrameBuffers.cpp \
	WaterRenderer.cpp \
	WaterShader.cpp \
	WaterTile.cpp

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
	-rm -f core \#*\# *~ *.o $(OBJECTS) $(TARGET)
