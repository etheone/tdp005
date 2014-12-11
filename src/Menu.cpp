/*
 * Menu.cpp
 *
 *  Created on: 11 dec 2014
 *      Author: joagy323
 */

#include "Menu.h"

using namespace std;

Menu::Menu(SDL_Renderer*& renderer) : Abstract_Gamestate(renderer), running{true}
{
	SDL_Surface* temp = IMG_Load("20x20_wall.png");
	textures["button1"] = SDL_CreateTextureFromSurface(renderer,temp);
	SDL_FreeSurface(temp);

	buttons["Play_Game"] = new Button(200, 200, 400, 400, textures["button1"]);

	run();
}

Menu::~Menu()
{
	//delete buttons;
	for(map<string, Button*>::iterator i = buttons.begin();
				i != buttons.end(); ++i)
		{
			delete i->second;
			i == nullptr;
		}

	for(map<string, SDL_Texture*&>::iterator i = textures.begin();
				i != textures.end(); ++i)
	{
		SDL_DestroyTexture(i->second);
	}
}

void Menu::draw_menu()
{
//	for(Button*& b : buttons)
//	{
//		b->render_copy(renderer);
//	}
}


void Menu::run()
{
	const Uint32 targetFrameDelay = 10;
	Uint32 startTime = SDL_GetTicks();
	Uint32 lastFrameTime = startTime;

	while(running)
	{
		Uint32 frameDelay = SDL_GetTicks() - lastFrameTime;
		lastFrameTime += frameDelay;

		//SDL_SetRelativeMouseMode(SDL_TRUE);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		draw_menu();

		//show the newly drawn things
		SDL_RenderPresent(renderer);

		// wait before drawing the next frame
		frameDelay = SDL_GetTicks() - lastFrameTime;
		if (targetFrameDelay > frameDelay)
		{
			// only wait if it's actually needed
			Uint32 sleepTime = targetFrameDelay - frameDelay;
			SDL_Delay(sleepTime);
		}
	}
}

