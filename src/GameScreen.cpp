/*
 * GameScreen.cpp
 *
 *  Created on: 5 dec 2014
 *      Author: joagy323
 */

#include "GameScreen.h"

using namespace std;

Game_Screen::Game_Screen(const int& screen_width, const int& screen_height)
: screen_width{screen_width} , screen_height{screen_height}
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		cerr << "Error initializing SDL" << endl;
		exit(1);
	}

	if (TTF_Init() != 0)
	{
		cerr << "Error initializing TTF" << endl;
		exit(1);
	}

		//create the window
		window = SDL_CreateWindow("SDL_Test",SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, 0);

		if (window == nullptr)
		{
			cerr <<  "SDL_CreateWindow error: " <<  SDL_GetError() << endl;
			SDL_Quit();
			exit(1);
		}

		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer == nullptr)
		{
			SDL_DestroyWindow(window);
			cerr << "SDL_CreateRenderer error: "
				 << SDL_GetError() << endl;
			SDL_Quit();
			exit(1);
		}

		// Make the scale rendering smoother
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
		// Render at a virtual resolution then stretch to actual resolution
		SDL_RenderSetLogicalSize(renderer, screen_width, screen_height);
}

Game_Screen::~Game_Screen()
{
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_Quit();
	TTF_Quit();
}

SDL_Renderer*& Game_Screen::get_renderer()
{
	return renderer;
}

