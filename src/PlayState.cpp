/*
 * PlayState.cpp
 *
 *  Created on: 29 nov 2014
 *      Author: joagy323
 */

#include "PlayState.h"

using namespace std;

Play_State::Play_State(SDL_Renderer*& renderer, Highscore_Menu*& highscore) :
		Abstract_Gamestate(renderer, "play_state"),
		current_time{1000},	level{nullptr},
		highscore{highscore}, current_level{1},
		space_down{false}, diff_x{0},
		diff_y{0}, angle_wait{0},
		shot_fired{0}, shot_hit{0}
{
}

Play_State::~Play_State()
{
	clear_play_state();
	TTF_CloseFont( font );
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

bool Play_State::player_clicked(int x, int y)
{
	bool check_x = level->player->get_left_x() < x &&
				   level->player->get_right_x() > x;
	bool check_y = level->player->get_top_y() < y &&
				   level->player->get_bottom_y() > y;
	return check_x && check_y;
}

void Play_State::handle_inputs()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			running = false;
			gamestate = "exit";
		}
		else if ((gamestate == "fail" || gamestate == "next_level") &&
				event.type == SDL_MOUSEBUTTONDOWN)
		{
			running = false;
		}
		else if ((gamestate == "freeze_state") &&
				(event.type == SDL_MOUSEBUTTONDOWN) &&
				player_clicked(event.motion.x, event.motion.y))
		{
			gamestate = "play_state";
			SDL_SetRelativeMouseMode(SDL_TRUE);

		}
		else if (gamestate == "play_state")
		{
			if(event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_p))
			{
				gamestate = "freeze_state";
				SDL_SetRelativeMouseMode(SDL_FALSE);
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
				diff_x += (event.motion.x - level->player->get_middle_x());
				diff_y += (event.motion.y - level->player->get_middle_y());
				++angle_wait;
				if (angle_wait >= 8 && !space_down)
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
				++shot_fired;
			}
		}
	}
}

void Play_State::run_game_loop()
{
	int time_count{0};
	const Uint32 targetFrameDelay = 10;
	Uint32 startTime = SDL_GetTicks();
	Uint32 lastFrameTime = startTime;

	while(running)
	{
		Uint32 frameDelay = SDL_GetTicks() - lastFrameTime;
		lastFrameTime += frameDelay;

		handle_inputs();

		if (level->player->get_health() <= 0)
		{
			gamestate = "fail";
			SDL_SetRelativeMouseMode(SDL_FALSE);
		}
		else if (level->no_enemies())
		{
			gamestate = "next_level";
			SDL_SetRelativeMouseMode(SDL_FALSE);
		}
		else if (gamestate == "play_state")
		{
			++time_count;
			level->update_enemy();
			level->enemy_collision_handler();
			level->player_collision_handler();
			if (time_count % 10 == 0)
			{
				--current_time;
			}

			if (!level->shots_empty())
			{
				level->update_shots();
			}
		}

		SDL_RenderClear(renderer);

		level->draw_level();
		load_temporary_texture( "Level " + to_string(current_level), 50, 5);
		load_temporary_texture( "Count down "+ to_string(current_time), 230, 5);
		load_temporary_texture( "Shots fired " + to_string(shot_fired), 570, 5);
		load_temporary_texture( "Shots hit " + to_string(shot_hit), 850, 5);
		if (gamestate == "freeze_state")
		{
			load_temporary_texture( "Click the pretty player-ship and prepare to rage", 230, 400);

		}
		else if (gamestate != "play_state")
		{
			load_temporary_texture( "Click anywhere on screen to continue", 300, 400);

		}
		if (gamestate == "fail")
		{
			load_temporary_texture( "FAIL!", 550, 300);
		}
		else if (gamestate == "next_level")
		{
			load_temporary_texture( "SUCCESS!", 520, 300);
		}

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
	gamestate = "freeze_state";

	level = new Level(renderer, shot_hit);
	level->load_level(current_level);

	run_game_loop();

	if (gamestate == "fail")
	{
		current_level = 1;
		current_time = 1000;
		shot_fired = 0;
		shot_hit = 0;
		gamestate = "menu";
	}
	else if (current_level == 3)
	{
		SDL_RenderClear(renderer);
		highscore->add_score(current_time, double(shot_hit) / double(shot_fired));
		current_level = 1;
		current_time = 1000;
		shot_fired = 0;
		shot_hit = 0;
		gamestate = "highscore";
	}
	else if (gamestate == "next_level")
	{
		++current_level;
		gamestate = "play_state";
	}

	clear_play_state();

	return gamestate;
}
