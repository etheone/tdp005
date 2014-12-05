/*
 * PlayState.cpp
 *
 *  Created on: 29 nov 2014
 *      Author: joagy323
 */

#include "PlayState.h"
#include <math.h>

using namespace std;

Play_State::Play_State(SDL_Renderer*& renderer) :
		Abstract_Gamestate(renderer), running{true}, player{nullptr}
{
	const char* ship_img{"draft.png"};

	player = new Player(0, 0, 0, ship_img, 1);
	player->loadTexture(renderer);
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
	for(Sprite* s : level_items)
	{
		delete s;
		s = nullptr;
	}


	// TODO Auto-generated destructor stub
}

void Play_State::set_up_level()
{
	const char* x_wall{"outer_x_wall.png"};
	const char* y_wall{"outer_y_wall.png"};
	const char* random_wall{"draft.png"};

	level_items.push_back(new Wall(0, 0, 0, x_wall));
	level_items.push_back(new Wall(0, SCREEN_HEIGHT-15, 0, x_wall));
	level_items.push_back(new Wall(SCREEN_WIDTH-15, 0, 0, y_wall));
	level_items.push_back(new Wall(0, 0, 0, y_wall));
	level_items.push_back(new Wall(200,200, 140, random_wall));

	for(Sprite*& sprite : level_items)
	{
		sprite->loadTexture(renderer);
	}
}

//void handle_keyboard_input(Player& player)

void Play_State::draw_level()
{
	for(Sprite*& sprite : level_items)
	{
		sprite->render_copy(renderer);
	}
}

double calculate_angle(double diff_x, double diff_y)
{
	const double rad_to_degree{180.0000 / 3.1416};
	return atan2 (diff_y, diff_x) * rad_to_degree;
}

bool Play_State::play_game()
{
	int angle{0};
	bool space_down{false};

	int count{0};
	double diff_x{0};
	double diff_y{0};
	set_up_level();

	const Uint32 targetFrameDelay = 10;
	Uint32 startTime = SDL_GetTicks();
	Uint32 lastFrameTime = startTime;

	while(running)
	{
		// calculate deltaTime to use for updates
		// done just before updates are done for maximum accuracy
		Uint32 frameDelay = SDL_GetTicks() - lastFrameTime;
		//float deltaTime = frameDelay / 1000.0f;
		lastFrameTime += frameDelay;

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
			}
			else if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_SPACE))
			{
				space_down = true;
			}
			else if (event.type == SDL_KEYUP && (event.key.keysym.sym == SDLK_SPACE))
			{
				space_down = false;
			}
			else if (event.type == SDL_MOUSEMOTION)
			{
				diff_x += (event.motion.x - player->get_x());
				diff_y += (event.motion.y - player->get_y());
				++count;
				if(count > 5 && !space_down)
				{
					angle = calculate_angle(diff_x, diff_y) + 90;
					count = 0;
					diff_x = 0;
					diff_y = 0;
					player->set_angle(angle);
				}

				player->set_position(
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
		//SDL_SetRelativeMouseMode(SDL_TRUE);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		draw_level();
		player->render_copy(renderer);

		//draw things

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

	return false;
}
