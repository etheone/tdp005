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

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
			if (renderer == nullptr)
			{
				SDL_DestroyWindow(window);
				cerr <<  "SDL_CreateRenderer error: "
					 <<  SDL_GetError() << endl;
				SDL_Quit();
				return 1;
			}

	//MAKE THE SCALE RENDERING SMOOTHER
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	//render at a virtual resolution then stretch to actual resolution
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);



	// CLASS INIT
	Play_State Play(renderer);

	// MAIN LOOP
	Play.play_game();




	//CLEANUP
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}
