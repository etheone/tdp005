#include <iostream>
#include "PlayState.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		cerr << "Error initializing SDL" << endl;
		exit(1);
	}
	//create the window
	SDL_Window* window = SDL_CreateWindow("SDL_Test",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
														SCREEN_WIDTH,SCREEN_HEIGHT, 0);
	if (window == nullptr)
	{
		cerr <<  "SDL_CreateWindow error: " <<  SDL_GetError() << endl;
		SDL_Quit();
		return 1;
	}


	// CLASS INIT
	Play_State Play(window);

	// MAIN LOOP
	Play.play_game();




	//CLEANUP
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}
