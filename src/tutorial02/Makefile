
#
# Generic Makefile to make one OpenGL based executable.
# Use GNU make .
#

SHELL	= /bin/sh

SOURCES = MainGameLoop.cpp DisplayManager.cpp RawModel.cpp Loader.cpp \
	Renderer.cpp
TARGET  = tutorial02
OBJECTS = $(SOURCES:.cpp=.o)

CC	= g++
SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)
CFLAGS	= -O2 -g -Wall $(SDL_CFLAGS)
LDFLAGS	= -L/usr/X11R6/lib -lGLEW -lGLU -lGL -lm $(SDL_LDFLAGS)


all: $(TARGET)
.PHONY: all


$(OBJECTS): %.o: %.cpp
	$(CC) -c $(CFLAGS) $^ -o $@

$(TARGET): $(OBJECTS)
	$(CC) $^ $(LDFLAGS) -o $@

.PHONY: clean
clean:
	-rm -f core \#*\# *~ *.o $(OBJECTS) $(TARGET)
