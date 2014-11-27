#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <emil>

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;

using namespace std;


int main(int argc, char* argv[])
{
	// initializing SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		cerr << "Error initializing SDL" << endl;
		exit(1);
	}

	//create the window
	SDL_Window* window = SDL_CreateWindow("SDL_Test",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_INPUT_GRABBED);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	//MAKE THE SCALE RENDERING SMOOTHER
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	//render at a virtual resolution then stretch to actual resolution
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	//main loop
	bool running{true};
	while (running)
	{
		//clear screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		//draw things

		//show the newly drawn things
		SDL_RenderPresent(renderer);

		//wait before drawing the next frame
		SDL_Delay(10);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}
