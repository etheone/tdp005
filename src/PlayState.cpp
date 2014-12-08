/*
 * PlayState.cpp
 *
 *  Created on: 29 nov 2014
 *      Author: joagy323
 */

#include "PlayState.h"

using namespace std;

Play_State::Play_State(SDL_Renderer*& renderer) :
		Abstract_Gamestate(renderer), running{true}, player{nullptr}
{
	const char* ship_img{"draft.png"};

	player = new Player(0, 0, 0, ship_img,renderer, 1);
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
	for(Wall*& s : level_items)
	{
		delete s;
		s = nullptr;
	}
	for(Shot*& s : shots)
	{
		delete s;
		s = nullptr;
	}

	for(Wall*& s : temp_shot_simulation)
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
	const char* random_wall{"200_inner_wall.png"};

	level_items.push_back(new Wall(0, 0, 90, x_wall, renderer));
	level_items.push_back(new Wall(0, SCREEN_HEIGHT-15, 90, x_wall, renderer));
	level_items.push_back(new Wall(SCREEN_WIDTH-15, 0, 0, y_wall, renderer));
	level_items.push_back(new Wall(0, 0, 0, y_wall, renderer));
	level_items.push_back(new Wall(400,400, 0, random_wall, renderer));


}

//void handle_keyboard_input(Player& player)

void Play_State::draw_level()
{
	for(Wall*& wall : level_items)
	{
		wall->render_copy(renderer);
	}

	for(Shot*& shot : shots)
	{
		shot->render_copy(renderer);
	}

	for(Wall*& w : temp_shot_simulation)
	{
		w->render_copy(renderer);
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
	{if(shots.size()  != 0)
	{
		if((*it)->get_bounce_count() == 0)
				{
					delete *it;
					shots.erase(it);
					break;
				}
		else
		{
			(*it)->update_pos();
		}
	}}
}

// Behövs till fienderna...
void Play_State::simulate_shot_path(Shot*& shot)
{

	double temp_x{shot->get_exact_x()};
	double temp_y{shot->get_exact_y()};
	double temp_angle{shot->get_angle()};
	int temp_bounce_count{shot->get_bounce_count()};

	while(shot->get_bounce_count() > 0)
	{
		for(Wall*& wall : level_items)
		{
			if(shot->intersect(wall))
			{
				cout << "true" << endl;
				shot->reduce_bounce_count();
				shot->set_angle((-shot->get_angle() + wall->get_angle()*2));
				shot->angle_to_queue(make_pair(shot->get_exact_x(), shot->get_exact_y()),shot->get_angle());
				//temp_shot_simulation.push_back(new Wall(shot->get_exact_x(),
//											   shot->get_exact_y(),
//												0, test_wall, renderer));
				break;
			}
		}
		shot->update_pos2();

	}
	shot->set_position(temp_x, temp_y);
	shot->set_angle(temp_angle);
	shot->set_bounce_count(temp_bounce_count);
}

bool Play_State::play_game()
{
	int angle{0};
	bool space_down{false};

	int count{0};
	double diff_x{0};
	double diff_y{0};
	set_up_level();

	const char* shot_img{"player_shot.png"};

	const Uint32 targetFrameDelay = 10;
	Uint32 startTime = SDL_GetTicks();
	Uint32 lastFrameTime = startTime;

	while(running)
	{
		// calculate deltaTime to use for updates
		// done just before updates are done for maximum accuracy
		Uint32 frameDelay = SDL_GetTicks() - lastFrameTime;
//		float deltaTime = frameDelay / 1000.0f;
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
				shots.push_back(new Shot(player->get_infront_x(),
										player->get_infront_y(),
										player->get_angle(), shot_img, 5, 4, renderer));
				simulate_shot_path(shots.back());

			}
		}



		if(!shots.empty())
		{
				update_shots();
		}

		//SDL_SetRelativeMouseMode(SDL_TRUE);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		draw_level();
		player->render_copy(renderer);

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
