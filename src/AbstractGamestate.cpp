/*
 * AbstractGamestate.cpp
 *
 *  Created on: 5 dec 2014
 *      Author: joagy323
 */

#include "AbstractGamestate.h"

using namespace std;

Abstract_Gamestate::Abstract_Gamestate(SDL_Window*& window)
	: renderer{SDL_CreateRenderer(window, -1, 0)}
{
	if (renderer == nullptr)
	{
		SDL_DestroyWindow(window);
		cerr <<  "SDL_CreateRenderer error: "
				<<  SDL_GetError() << endl;
		SDL_Quit();
		exit(1);
	}

//MAKE THE SCALE RENDERING SMOOTHER
SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
//render at a virtual resolution then stretch to actual resolution
SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

Abstract_Gamestate::~Abstract_Gamestate()
{
	// TODO Auto-generated destructor stub
}

