XXFLAGS=-Wall -Wextra -std=c++11 -Wno-unused-parameter
SDL_FLAGS=`sdl2-config --libs --cflags` -lSDL2_image
SRC_DIR=src

all: main

main: $(SRC_DIR)/main.cc
	g++ $(CXXFLAGS) $(SRC_DIR)/main.cc -o main $(SDL_FLAGS)


.PHONY clean:
	rm -f main
