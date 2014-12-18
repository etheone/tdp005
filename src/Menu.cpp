/*
 * Menu.cpp
 *
 *  Created on: 11 dec 2014
 *      Author: joagy323
 */

#include "Menu.h"

using namespace std;

Menu::Menu(SDL_Renderer*& renderer)
: Abstract_Gamestate(renderer, "menu")
{
	SDL_Surface* temp = IMG_Load("textures/start_button.png");
	textures["button1"] = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	temp = IMG_Load("textures/highscore_button.png");
	textures["button2"] = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	temp = IMG_Load("textures/quit_button.png");
	textures["button3"] = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	buttons["start_game"] = new Button(500, 190, 187, 85, textures["button1"]);
	buttons["highscore_button"] = new Button(420, 320, 355, 166, textures["button2"]);
	buttons["quit_game"] = new Button(500, 520, 174, 100, textures["button3"]);
}

Menu::~Menu()
{
	//delete buttons;
	for (map<string, Button*>::iterator i = buttons.begin();
				i != buttons.end(); ++i)
	{
		delete i->second;
		i->second = nullptr;
	}

	//delete textures
	for (map<string, SDL_Texture*>::iterator i = textures.begin();
				i != textures.end(); ++i)
	{
		SDL_DestroyTexture(i->second);
	}

	TTF_CloseFont(font);
}

void Menu::draw_menu()
{
	for (map<string, Button*>::iterator i = buttons.begin();
					i != buttons.end(); ++i)
	{
		i->second->render_copy(renderer);
	}
}

void Menu::handle_inputs()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT ||
		   (event.type == SDL_MOUSEBUTTONDOWN &&
				   buttons["quit_game"]->in_button_area(event.motion.x, event.motion.y)))
		{
			running = false;
			gamestate = "exit";
		}
		else if ( event.type == SDL_MOUSEBUTTONDOWN &&
				 buttons["start_game"]->in_button_area(event.motion.x, event.motion.y))
		{
			running = false;
			gamestate = "play_state";
		}
		else if ( event.type == SDL_MOUSEBUTTONDOWN &&
						 buttons["highscore_button"]->in_button_area(event.motion.x, event.motion.y))
		{
			running = false;
			gamestate = "highscore";
		}
	}
}

string Menu::run()
{
	running = true;
	gamestate = "none";

	const Uint32 targetFrameDelay = 10;
	Uint32 startTime = SDL_GetTicks();
	Uint32 lastFrameTime = startTime;

	while (running)
	{
		Uint32 frameDelay = SDL_GetTicks() - lastFrameTime;
		lastFrameTime += frameDelay;

		SDL_SetRelativeMouseMode(SDL_FALSE);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		draw_menu();
		handle_inputs();

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

	return gamestate;
}

