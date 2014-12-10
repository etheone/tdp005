# Kompilatorn som ska användas:
CC=g++
SRC_DIR=src
# Flaggorna till kompilatorn:
CFLAGS=-g -c -std=c++11 -Wall -Wextra -Wpedantic -ggdb -Wno-unused-parameter -I$(SRC_DIR)
# Flaggorna till länkaren:
LFLAGS=-lSDL2main -lSDL2 -lSDL2_image

all: Starcrossed

Starcrossed: main.o PlayState.o wall.o Sprite.o Shot.o Player.o AbstractGamestate.o GameScreen.o Animation.o Image.o
	$(CC) *.o  $(LFLAGS) -o Starcrossed

main.o: $(SRC_DIR)/main.cc
	$(CC) $(CFLAGS) $(SRC_DIR)/main.cc

Sprite.o: $(SRC_DIR)/Sprite.cpp $(SRC_DIR)/Sprite.h
	$(CC) $(CFLAGS) $(SRC_DIR)/Sprite.cpp
	
Player.o: $(SRC_DIR)/Player.cpp $(SRC_DIR)/Player.h
	$(CC) $(CFLAGS) $(SRC_DIR)/Player.cpp
	
wall.o: $(SRC_DIR)/wall.cpp $(SRC_DIR)/wall.h
	$(CC) $(CFLAGS) $(SRC_DIR)/wall.cpp

PlayState.o: $(SRC_DIR)/PlayState.cpp $(SRC_DIR)/PlayState.h
	$(CC) $(CFLAGS) $(SRC_DIR)/PlayState.cpp	
	
AbstractGamestate.o: $(SRC_DIR)/AbstractGamestate.cpp $(SRC_DIR)/AbstractGamestate.h
	$(CC) $(CFLAGS) $(SRC_DIR)/AbstractGamestate.cpp
	
GameScreen.o: $(SRC_DIR)/GameScreen.cpp $(SRC_DIR)/GameScreen.h
	$(CC) $(CFLAGS) $(SRC_DIR)/GameScreen.cpp
	
Shot.o: $(SRC_DIR)/Shot.cpp $(SRC_DIR)/Shot.h
	$(CC) $(CFLAGS) $(SRC_DIR)/Shot.cpp
	
Image.o: $(SRC_DIR)/Image.cpp $(SRC_DIR)/Image.h
	$(CC) $(CFLAGS) $(SRC_DIR)/Image.cpp
	
Animation.o: $(SRC_DIR)/Animation.cpp $(SRC_DIR)/Animation.h
	$(CC) $(CFLAGS) $(SRC_DIR)/Animation.cpp

clean:
	rm -rf *.o Starcrossed
