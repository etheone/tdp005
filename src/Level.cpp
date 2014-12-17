/*
 * Level.cpp
 *
 *  Created on: 10 dec 2014
 *      Author: joagy323
 */

#include "Level.h"

using namespace std;

Level::Level(SDL_Renderer*& renderer, int& level_time, int& shot_hit)
:  player{nullptr}, level_time{level_time},
   shot_hit{shot_hit}, renderer{renderer},
   back({0, 50, 1200, 800})
{
	SDL_Surface* temp = IMG_Load("textures/20x20_wall.png");
	textures["wall"] = SDL_CreateTextureFromSurface(renderer,temp);
	SDL_FreeSurface(temp);

	temp = IMG_Load("textures/playership.png");
	textures["player"] = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	temp = IMG_Load("textures/player_shot4x4.png");
	textures["shot"] = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	temp = IMG_Load("textures/enemy_shot.png");
	textures["enemy_shot"] = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	temp = IMG_Load("textures/shotspritesheet.png");
	textures["shot_animation"] = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	temp = IMG_Load("textures/enemyship1.png");
	textures["enemy"] = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	temp = IMG_Load("textures/shipexplosion.png");
	textures["ship_explosion"] = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	temp = IMG_Load("textures/space1.png");
	textures["background"] = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	level_items.push_back(new Wall(0, 50, 1200, 20, textures["wall"]));
	level_items.push_back(new Wall(0, SCREEN_HEIGHT-20, 1200, 20, textures["wall"]));
	level_items.push_back(new Wall(SCREEN_WIDTH-20, 50, 20, 850, textures["wall"]));
	level_items.push_back(new Wall(0, 50, 20, 850, textures["wall"]));
}

Level::~Level()
{
	clear_level();
}

void Level::clear_level()
{
	delete player;
		player = nullptr;

		for (Enemy*& e : enemies)
			{
				delete e;
				e = nullptr;
			}

		for (Shot*& s : shots)
		{
			delete s;
			s = nullptr;
		}

		for (Animation*& a : animations)
		{
			delete a;
			a = nullptr;
		}

		for (map<string, SDL_Texture*>::iterator i = textures.begin();
				i != textures.end(); ++i)
		{
			SDL_DestroyTexture(i->second);
		}

		for (Sprite*& l : level_items)
		{
			delete l;
			l = nullptr;
		}
}

bool Level::combine_y_walls(const int& x, const int& y)
{
	for (Sprite*& wall : level_items)
	{
		if (wall->get_left_x() == x &&
			wall->get_half_width()*2 == 20 &&
			wall->get_bottom_y() == y)
		{
			wall->increase_height(20);
			return true;
		}
	}
	return false;
}

void Level::load_level(const int& level)
{
	// Loads a level from a file.
	// If there are severals wall objects next to each other, they are combined
	// into a single larger wall to reduce the amount of wall objects in play

	string level_str = "levels/level" + to_string(level)+ ".txt";
	ifstream file(level_str);
	string line{""};

	int last_wall_left{-1};

	for (int line_number{3}; line_number < 44; ++line_number)
	{
		last_wall_left = -1;
		getline(file, line);
		for (int i{1}; i < 60 && i < int(line.length()); ++i)
		{
			if (line[i] == '#')
			{
				if (last_wall_left == i-1)
				{
					level_items.back()->increase_width(20);
					last_wall_left = i;
				}

				else if (!combine_y_walls(i*20, line_number*20))
				{
					level_items.push_back(new Wall(i*20, line_number*20,
										  20, 20, textures["wall"]));
					last_wall_left = i;
				}
			}

			if (line[i] == 'p')
			{
				player = new Player(i*20 ,line_number*20, 40,
									40, 180, textures["player"], 1);
			}

			if (line[i] == 'e')
			{
				enemies.push_back(new Enemy(i*20, line_number*20,
								  60, 60, 270, textures["enemy"], 5));
			}
		}
	}

	file.close();
}

bool Level::no_enemies()
{
	return enemies.empty();
}

void Level::draw_level()
{
	SDL_RenderCopy(renderer, textures["background"], nullptr, &back);

	player->render_copy(renderer);

	for (Enemy*& enemy : enemies)
	{
		enemy->render_copy(renderer);
	}

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

void Level::update_time()
{
	--level_time;
}

void Level::update_enemy()
{
	for (vector<Enemy*>::iterator it{enemies.begin()}; it != enemies.end(); ++it)
	{
		if ((*it)->get_health() <= 0)
		{
			animations.push_back(new Animation(textures["ship_explosion"],
											(*it)->get_middle_x(),
											(*it)->get_middle_y(),
											480, 60,
											8, 5));
			delete (*it);
			enemies.erase(it);
			break;
		}

		if ((*it)->get_counter() == 40)
		{
			add_to_shots((*it)->get_middle_x(),
						 (*it)->get_middle_y(),
						 4, 4,
						 (*it)->get_angle(),
						 5, 3, false, "enemy_shot");
			simulate_shot_path();
		}

		(*it)->update(level_items);
	}
}

void Level::update_shots()
{
	for (vector<Shot*>::iterator it{shots.begin()}; it != shots.end(); ++it)
	{
		if ((*it)->get_bounce_count() < 0 || (*it)->outside_screen())
		{
			animations.push_back(new Animation(textures["shot_animation"],
								(*it)->get_left_x(),
								(*it)->get_top_y(),
								256, 32,
								8, 3));
			delete *it;
			shots.erase(it);
			break;
		}
		else
		{
			Sprite* temp;
			for (Enemy* enemy : enemies)
			{
				temp = dynamic_cast<Sprite*>(enemy);
				if ((*it)->is_player_shot() && (*it)->intersect(temp))
				{
					animations.push_back(new Animation(textures["shot_animation"],
													(*it)->get_left_x(),
													(*it)->get_top_y(),
													256, 32,
													8, 3));
					enemy->decrease_health();
					delete *it;
					shots.erase(it);
					++shot_hit;
					return;
				}
			}
			temp = nullptr;

			(*it)->update_pos();
		}
	}
}

void Level::add_to_shots(const double& x, const double& y, const int& w, const int& h,
				         const double& angle, const int& speed, const int& b,
						 const bool& player_shot, string text)
{
	shots.push_back(new Shot(x, y, w, h, angle,
							 textures[text],
							 speed, b, player_shot));
}

int Level::get_time() const
{
	return level_time;
}

void Level::enemy_collision_handler()
{
	Sprite* e{nullptr};

	for (Enemy*& enemy : enemies)
	{
		e = dynamic_cast<Sprite*>(enemy);
		if (player->intersect(e))
		{
		player->set_visible(false);
		player->decrease_health();
		animations.push_back(new Animation(textures["ship_explosion"],
				player->get_middle_x(),
				player->get_middle_y(),
				480, 60,
				8, 20));
		}
	}

	e = nullptr;
}

bool Level::shots_empty()
{
	return shots.empty();
}


void Level::player_collision_handler()
{
	Sprite* p = dynamic_cast<Sprite*>(player);

	for (Sprite*& s : level_items)
	{
		if (s->intersect(p))
		{
			cout << "you crashed" << endl;
			player->decrease_health();
			animations.push_back(new Animation(textures["ship_explosion"],
														player->get_middle_x(),
														player->get_middle_y(),
														480, 60,
														8, 20));
			player->set_visible(false);
		}
	}

	for (Shot*& s : shots)
	{
		if (s->intersect(p) && (s->get_harmless_time() > 40 || !(s->is_player_shot())))
		{
			player->decrease_health();
			animations.push_back(new Animation(textures["ship_explosion"],
																	player->get_middle_x(),
																	player->get_middle_y(),
																	480, 60,
																	8, 20));
			player->set_visible(false);
		}
	}

	p = nullptr;
}

void Level::simulate_shot_path()
{
	Shot*& shot{shots.back()};
	double temp_x{shot->get_left_x()};
	double temp_y{shot->get_top_y()};
	double temp_angle{shot->get_angle()};
	int temp_bounce_count{shot->get_bounce_count()};

	while (shot->get_bounce_count() >= 0 && !shot->outside_screen())
	{
		for (Sprite*& sprite : level_items)
		{
			if (shot->intersect(sprite))
			{
				shot->move_back();
				shot->reduce_bounce_count();
				shot->set_angle(shot->calculate_angle_update(sprite));
				shot->angle_to_queue(
						make_pair(shot->get_left_x(), shot->get_top_y()),
						shot->get_angle());
			}
		}

		shot->update_pos_simulation();
	}

	shot->set_position(temp_x, temp_y);
	shot->set_angle(temp_angle);
	shot->set_bounce_count(temp_bounce_count);
}

