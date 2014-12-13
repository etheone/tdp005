/*
 * PlayState.cpp
 *
 *  Created on: 29 nov 2014
 *      Author: joagy323
 */

#include "PlayState.h"

using namespace std;

Play_State::Play_State(SDL_Renderer*& renderer) :
		Abstract_Gamestate(renderer, "play_state"), score{0}, running{true},
		level{nullptr}, space_down{false},
		diff_x{0}, diff_y{0}, angle_wait{0}, pause{false}
{
}

Play_State::~Play_State()
{
	clear_play_state();

}

void Play_State::clear_play_state()
{
	delete level;
	level = nullptr;
}


double calculate_angle(double diff_x, double diff_y)
{
	const double rad_to_degree{180.0000 / 3.1416};
	return atan2 (diff_y, diff_x) * rad_to_degree;
}


void Play_State::handle_inputs()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT ||
				((gamestate != "play_state") &&
				(event.type == SDL_MOUSEBUTTONDOWN)))
		{
			running = false;
		}
		else if(gamestate == "play_state")
		{
			if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_SPACE))
			{
				space_down = true;
			}
			else if (event.type == SDL_KEYUP && (event.key.keysym.sym == SDLK_SPACE))
			{
				space_down = false;
			}
			else if (event.type == SDL_MOUSEMOTION)
			{
				diff_x += (event.motion.x - level->player->get_middle_x());
				diff_y += (event.motion.y - level->player->get_middle_y());
				++angle_wait;
				if(angle_wait >= 8 && !space_down)
				{
					level->player->set_angle(calculate_angle(diff_x, diff_y) + 90);
					angle_wait = 0;
					diff_x = 0;
					diff_y = 0;
				}
				level->player->set_position(
						event.motion.x - level->player->get_half_width(),
						event.motion.y - level->player->get_half_height());

			}
			else if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				level->add_to_shots(level->player->get_middle_x(),
									level->player->get_middle_y(),
									4, 4,
									level->player->get_angle(),
									5, 3, true);
				level->simulate_shot_path();
			}
		}
	}
}

void Play_State::run_game_loop()
{
	//bool level_complete{false};
	//bool game_over{false};
	const Uint32 targetFrameDelay = 10;
	Uint32 startTime = SDL_GetTicks();
	Uint32 lastFrameTime = startTime;

	while(running)
	{
		Uint32 frameDelay = SDL_GetTicks() - lastFrameTime;
		lastFrameTime += frameDelay;

		handle_inputs();
		if(level->player->get_health() <= 0)
		{
			//game_over = true;
			gamestate = "menu";
			SDL_SetRelativeMouseMode(SDL_FALSE);
		}
		else if(level->no_enemies())
		{
			// level_complete = true;
			gamestate = "YOU WON!";
			SDL_SetRelativeMouseMode(SDL_FALSE);
		}
		else
		{
			level->update_enemy();
			level->enemy_collision_handler();
			level->player_collision_handler();

			if(!level->shots_empty())
			{
				level->update_shots();
			}
		}

		//SDL_SetRelativeMouseMode(SDL_TRUE);
		//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		level->draw_level();

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

string Play_State::run()
{
	running = true;
	space_down = false;
	gamestate = "play_state";
	SDL_SetRelativeMouseMode(SDL_TRUE);

	level = new Level(renderer);
	level->load_level("1");

	run_game_loop();
	clear_play_state();

	return gamestate;
}
