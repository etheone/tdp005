/*
 * PlayState.cpp
 *
 *  Created on: 29 nov 2014
 *      Author: joagy323
 */

#include "PlayState.h"

Play_State::Play_State(SDL_Renderer*& renderer) :
renderer{renderer}, running{true}, player{nullptr}
{
	const char* ship_img{"draft.png"};

	player = new Player(0,0);
	player->loadTexture(ship_img, renderer);
	// TODO Auto-generated constructor stub
}

Play_State::~Play_State()
{
	//for(std::pair<std::string, Sprite*> p : level_items)
//	{
//		delete p.second;
//	}
	delete player;
	player = nullptr;
	//SDL_DestroyRenderer(renderer);
	renderer = nullptr;

	// TODO Auto-generated destructor stub
}

void Play_State::set_up_map()
{
}

bool Play_State::play_game()
{
	int angle{0};
	while(running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			++angle;
			player->set_angle(angle);

			if (event.type == SDL_QUIT)
			{
				running = false;
			}
			else if (event.type == SDL_MOUSEMOTION)
			{
				player->set_new_position(
						event.motion.x - (player->get_half_width()),
						event.motion.y - (player->get_half_height())
										);
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				std::cout << "click" << std::endl;
			}

		}
		//clear screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		player->render_copy(renderer);
		//draw things

		//show the newly drawn things
		SDL_RenderPresent(renderer);


		//wait before drawing the next frame
		SDL_Delay(20);

	}

	return false;
}
