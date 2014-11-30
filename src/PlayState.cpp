/*
 * PlayState.cpp
 *
 *  Created on: 29 nov 2014
 *      Author: joagy323
 */

#include "PlayState.h"
#include <math.h>

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

double calculate_angle(int diff_x, int diff_y)
{
	const double rad_to_degree{180.0000 / 3.1416};
	std::cout << "now " << diff_x << diff_y << std::endl;
	return atan2 (double(diff_y), double(diff_x)) * rad_to_degree;

	/*if(diff_y < 0)
	{
		return atan (diff_x / diff_y) * -rad_to_degree;
	}
	else if (diff_y >= 0)
	{
		if (diff_x < 0)
		{
			return (atan (diff_y / diff_x) * rad_to_degree) - 90;
		}
		else if (diff_x > 0)
		{
			return (atan (diff_y / diff_x) *rad_to_degree) + 90;
		}
	}
	return 180;*/
}

bool Play_State::play_game()
{
	int angle{0};
	int count{0};
	while(running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{

			if (event.type == SDL_QUIT)
			{
				running = false;
			}
			else if (event.type == SDL_MOUSEMOTION)
			{
				int diff_x{event.motion.x - player->get_x()};
				int diff_y{event.motion.y - player->get_y()};
				if(diff_x == 0 || diff_y == 0)
				{
					++count;
					std::cout << "NU" ;
				}
				else {count = 3;}
				if(count > 2)
				{
					angle = calculate_angle(diff_x,diff_y);
					count = 0;
				}

				std::cout << angle << std::endl;
				player->set_angle(angle);
				player->set_new_position(
						event.motion.x - (player->get_half_width()),
						event.motion.y - (player->get_half_height())
										);
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				std::cout << "click" << std::endl;
			}

			player->render_copy(renderer);

		}

		//clear screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		player->render_copy(renderer);
		//draw things

		//show the newly drawn things
		SDL_RenderPresent(renderer);



			SDL_Delay(10);

	}

	return false;
}
