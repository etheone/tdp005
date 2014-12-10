/*
 * PlayState.cpp
 *
 *  Created on: 29 nov 2014
 *      Author: joagy323
 */

#include "PlayState.h"

using namespace std;

const char* COIN{"coin.png"};
const char* SHOT_IMG{"player_shot4x4.png"};
const char* ENEMY_SHOT{"enemy_shot.png"};
const char* SHIP_IMG{"draft2.png"};
const char* x_wall{"outer_x_wall.png"};
const char* y_wall{"outer_y_wall.png"};
const char* random_wall{"200_inner_wall.png"};
const char* X_90_WALL{"100_inner_horizontal.png"};

Play_State::Play_State(SDL_Renderer*& renderer) :
		Abstract_Gamestate(renderer), running{true}, space_down{false},
		diff_x{0}, diff_y{0}, angle_wait{0}, pause{false}, player{nullptr}
{
	player = new Player(0, 0, 0, SHIP_IMG,renderer, 1);
}

Play_State::~Play_State()
{
	delete player;
	player = nullptr;
	for(Sprite*& s : level_items)
	{
		delete s;
		s = nullptr;
	}
	for(Shot*& s : shots)
	{
		delete s;
		s = nullptr;
	}
	for(Animation*& a : animations)
		{
			delete a;
			a = nullptr;
		}
}

void Play_State::set_up_level()
{
	level_items.push_back(new Wall(0, 0, 90, x_wall, renderer));
	level_items.push_back(new Wall(0, SCREEN_HEIGHT-15, 90, x_wall, renderer));
	level_items.push_back(new Wall(SCREEN_WIDTH-15, 0, 0, y_wall, renderer));
	level_items.push_back(new Wall(0, 0, 0, y_wall, renderer));
	level_items.push_back(new Wall(400,400, 0, random_wall, renderer));
	level_items.push_back(new Wall(400,400, 90, X_90_WALL, renderer));
	level_items.push_back(new Wall(500,400, 0, random_wall, renderer));
	level_items.push_back(new Wall(400,588, 90, X_90_WALL, renderer));
	level_items.push_back(new Wall(700,388, 90, X_90_WALL, renderer));
}

//void handle_keyboard_input(Player& player)

void Play_State::draw_level()
{
	player->render_copy(renderer);

	for (Sprite*& sprite : level_items)
	{
		sprite->render_copy(renderer);
	}

	for (Shot*& shot : shots)
	{
		shot->render_copy(renderer);
	}
	for (vector<Animation*>::iterator it{animations.begin()};
			it != animations.end();
			++it)
	{
		if ((*it)->is_alive())
		{
			(*it)->render_copy(renderer);
			(*it)->update();
		}
		else
		{
			delete *it;
			animations.erase(it);
			break;
		}
	}
}

double calculate_angle(double diff_x, double diff_y)
{
	const double rad_to_degree{180.0000 / 3.1416};
	return atan2 (diff_y, diff_x) * rad_to_degree;
}

void Play_State::update_shots()
{
	for(vector<Shot*>::iterator it{shots.begin()}; it !=shots.end(); ++it)
	{
		if ((*it)->get_bounce_count() <= 0 || (*it)->outside_screen())
		{
			animations.push_back(new Animation(renderer,
								(*it)->get_left_x(),
								(*it)->get_top_y(),
								9, 20, COIN));
			delete *it;
			shots.erase(it);
			break;
		}
		else
		{
			(*it)->update_pos();
		}
	}
}

void Play_State::player_collision_handler()
{
	for(Sprite*& s : level_items)
	{
		if(s->intersect(player))
		{
			cout << "you crashed" << endl;
		}
	}
	for(Shot*& s : shots)
	{
		if(s->intersect(player) && s->get_harmless_time() > 20)
		{
			cout << "you ded" << endl;
		//	pause = true;
			//running = false;
		}
	}
}

double calculate_shot_angle(Shot*& shot, Sprite*& sprite)
{
	if(shot->check_left_short_side_collision(sprite) ||
	   shot->check_right_short_side_collision(sprite))
	{
		cout << "now" << endl;
		return (-shot->get_angle() + sprite->get_angle() * 2) + 180;
	}

	return (-shot->get_angle() + sprite->get_angle() * 2);
}

// Behövs till fienderna...
void Play_State::simulate_shot_path(Shot*& shot)
{
	double temp_x{shot->get_left_x()};
	double temp_y{shot->get_top_y()};
	double temp_angle{shot->get_angle()};
	int temp_bounce_count{shot->get_bounce_count()};

	while (shot->get_bounce_count() >= 0)
	{
		for (Sprite*& sprite : level_items)
		{
			if (shot->intersect(sprite))
			{	shot->reduce_bounce_count();
				shot->set_angle(calculate_shot_angle(shot, sprite));
				shot->move_back();
				shot->angle_to_queue(
						make_pair(shot->get_left_x(), shot->get_top_y()),
						shot->get_angle());
				//level_items.push_back(new Wall(shot->get_left_x(),shot->get_top_y(), 90, ENEMY_SHOT, renderer));
				break;
			}
		}
		shot->update_pos_simulation();
	}
	shot->set_position(temp_x, temp_y);
	shot->set_angle(temp_angle);
	shot->set_bounce_count(temp_bounce_count);
}

void Play_State::handle_inputs()
{
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
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
		{
			pause = true;
			running = false;
		}
		else if (event.type == SDL_MOUSEMOTION)
		{
			diff_x += (event.motion.x - player->get_middle_x());
			diff_y += (event.motion.y - player->get_middle_y());
			++angle_wait;
			if(angle_wait >= 5 && !space_down)
			{
				player->set_angle(calculate_angle(diff_x, diff_y) + 90);
				angle_wait = 0;
				diff_x = 0;
				diff_y = 0;
			}
			player->set_position(
					event.motion.x - player->get_half_width(),
					event.motion.y - player->get_half_height());
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			shots.push_back(new Shot(player->get_middle_x(),
					player->get_middle_y(),
					player->get_angle(), SHOT_IMG, 5, 5, renderer));
			simulate_shot_path(shots.back());
		}
	}
}

void Play_State::run_game_loop()
{
	const Uint32 targetFrameDelay = 10;
	Uint32 startTime = SDL_GetTicks();
	Uint32 lastFrameTime = startTime;

	while(running)
	{
		// calculate deltaTime to use for updates
		// done just before updates are done for maximum accuracy
		Uint32 frameDelay = SDL_GetTicks() - lastFrameTime;
		lastFrameTime += frameDelay;

		handle_inputs();
		player_collision_handler();

		if(!shots.empty())
		{
			update_shots();
		}

		//SDL_SetRelativeMouseMode(SDL_TRUE);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		draw_level();

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

bool Play_State::play_game()
{
	set_up_level();

	run_game_loop();

	// Handles Pause-button.
	SDL_Event event;
	while(pause)
	{
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT)
			{
				pause = false;
			}
		else if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_p))
		{
			pause = false;
			running = true;
			run_game_loop();
		}
	}

	return false;
}
