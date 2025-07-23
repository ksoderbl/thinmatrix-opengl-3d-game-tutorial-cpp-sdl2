#
# Generic Makefile to make one OpenGL based executable.
# Use GNU make .
#

SHELL	= /bin/sh

SOURCES = MainGameLoop.cpp DisplayManager.cpp RawModel.cpp Loader.cpp \
	EntityRenderer.cpp ShaderProgram.cpp StaticShader.cpp \
	ModelTexture.cpp TexturedModel.cpp Maths.cpp Entity.cpp \
	Camera.cpp Keyboard.cpp Light.cpp MasterRenderer.cpp \
	Terrain.cpp TerrainShader.cpp TerrainRenderer.cpp \
	Vertex.cpp ModelData.cpp OBJFileLoader.cpp \
	TerrainTexture.cpp TerrainTexturePack.cpp Player.cpp \
	Mouse.cpp
TARGET  = tutorial20
OBJECTS = $(SOURCES:.cpp=.o)

CC	= g++
SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)
CFLAGS	= -O2 -g -Wall $(SDL_CFLAGS)
LDFLAGS	= -L/usr/X11R6/lib -lGLEW -lGLU -lGL -lm $(SDL_LDFLAGS) -lpng


all: $(TARGET)
.PHONY: all


$(OBJECTS): %.o: %.cpp
	$(CC) -c $(CFLAGS) $^ -o $@

$(TARGET): $(OBJECTS)
	$(CC) $^ $(LDFLAGS) -o $@

.PHONY: clean
clean:
	-rm -f core \#*\# *~ *.o $(OBJECTS) $(TARGET)
