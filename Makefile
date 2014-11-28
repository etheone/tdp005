# Kompilatorn som ska användas:
CC=g++
#CXXFLAGS=-Wall -Wextra -std=c++11 -Wno-unused-parameter
#SDL_FLAGS=`sdl2-config --libs --cflags` -lSDL2_image

SRC_DIR=src
# Flaggorna till kompilatorn:
CFLAGS=-g -c -std=c++11 -Wall -Wextra -Wpedantic -ggdb -Wno-unused-parameter -I$(SRC_DIR)
# Flaggorna till länkaren:
LFLAGS=-lSDL2main -lSDL2 -lSDL2_image


all: Starcrossed

Starcrossed: main.o Gameengine.o 
	$(CC) *.o  $(LFLAGS) -o Starcrossed

main.o: $(SRC_DIR)/main.cc
	$(CC) $(CFLAGS) $(SRC_DIR)/main.cc
	
Gameengine.o: $(SRC_DIR)/Gameengine.cpp $(SRC_DIR)/Gameengine.h
	$(CC) $(CFLAGS) $(SRC_DIR)/Gameengine.cpp
	

.PHONY clean:
	rm -f main
