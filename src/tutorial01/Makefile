#
# Generic Makefile to make one OpenGL based executable.
# Use GNU make .
#

SHELL	= /bin/sh

SOURCES = \
	engineTester/MainGameLoop.cpp \
	renderEngine/DisplayManager.cpp

TARGET  = tutorial01
OBJECTS = $(SOURCES:.cpp=.o)

CC	= g++
SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)
CFLAGS	= -O2 -Wall -std=c++11 $(SDL_CFLAGS)
LDFLAGS	= -lGLEW -lGLU -lGL -lm $(SDL_LDFLAGS)


all: $(TARGET)
.PHONY: all


$(OBJECTS): %.o: %.cpp
	$(CC) -c $(CFLAGS) $^ -o $@

$(TARGET): $(OBJECTS)
	$(CC) $^ $(LDFLAGS) -o $@

.PHONY: clean
clean:
	-rm -f core \#*\# *~ */*~ *.o */*.o $(TARGET)
