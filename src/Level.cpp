/*
 * Level.cpp
 *
 *  Created on: 10 dec 2014
 *      Author: joagy323
 */

#include "Level.h"

using namespace std;

Level::Level(SDL_Renderer*& renderer)
:player{nullptr}, current_level{"1"}, renderer{renderer}, back({0, 0, 1200, 800})
{
	SDL_Surface* temp = IMG_Load("textures/20x20_wall.png");
	textures["wall"] = SDL_CreateTextureFromSurface(renderer,temp);
	SDL_FreeSurface(temp);

	temp = IMG_Load("textures/outer_x_wall.png");
	textures["outer_x"] = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	temp = IMG_Load("textures/outer_y_wall.png");
	textures["outer_y"] = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	temp = IMG_Load("textures/playership.png");
	textures["player"] = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	temp = IMG_Load("textures/player_shot4x4.png");
	textures["shot"] = SDL_CreateTextureFromSurface(renderer, temp);
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


	level_items.push_back(new Wall(0, 0, 1200, 15, textures["outer_x"]));
	level_items.push_back(new Wall(0, SCREEN_HEIGHT-15, 1200, 15, textures["outer_x"]));
	level_items.push_back(new Wall(SCREEN_WIDTH-15, 0, 15, 800, textures["outer_y"]));
	level_items.push_back(new Wall(0, 0, 15, 800, textures["outer_y"]));
}

Level::~Level()
{
	clear_level();
}

void Level::clear_level()
{
	delete player;
		player = nullptr;

		for(Enemy*& e : enemies)
			{
				delete e;
				e = nullptr;
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

		for(map<string, SDL_Texture*>::iterator i = textures.begin();
				i != textures.end(); ++i)
		{
			SDL_DestroyTexture(i->second);
		}

		for(Sprite*& l : level_items)
		{
			delete l;
			l = nullptr;
		}
}


void Level::load_level(string filenumber)
{
	// Loads a level from a file.

	current_level = filenumber;
	string level_str = "levels/level" + current_level + ".txt";
	ifstream file(level_str);
	string line{""};

	for(int line_number{1}; line_number < 40; ++line_number)
	{
		getline(file, line);
		for (unsigned int i{1}; i < 60 && i < line.length(); ++i)
		{
			if (line[i] == '#')
			{
				level_items.push_back(new Wall(i*20, line_number*20, 20, 20, textures["wall"]));
			}

			if (line[i] == 'p')
			{
				player = new Player(i*20 ,line_number*20 ,40, 40, 180, textures["player"], 1);
			}

			if (line[i] == 'e')
			{
				enemies.push_back(new Enemy(i*20, line_number*20, 60, 60, 270, textures["enemy"], 5));
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
//std::string score_text = "score: " + std::to_string(score);
//SDL_Color textColor = { 255, 255, 255, 0 };
//SDL_Surface* textSurface = TTF_RenderText_Solid(font, score_text.c_str(), textColor);
//SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, textSurface);
//int text_width = textSurface->w;
//int text_height = textSurface->h;
//SDL_FreeSurface(textSurface);
//SDL_Rect renderQuad = { 20, win_height - 30, text_width, text_height };
//SDL_RenderCopy(renderer, text, NULL, &renderQuad);
//SDL_DestroyTexture(text);

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

void Level::update_enemy()
{
	for(vector<Enemy*>::iterator it{enemies.begin()}; it != enemies.end(); ++it)
	{
		if((*it)->get_health() <= 0)
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

		if((*it)->get_counter() == 40)
		{
			add_to_shots((*it)->get_middle_x(),
						 (*it)->get_middle_y(),
						 4, 4,
						 (*it)->get_angle(),
						 5, 3, false);
			simulate_shot_path();
		}
		(*it)->update();
	}
}

void Level::update_shots()
{
	for(vector<Shot*>::iterator it{shots.begin()}; it != shots.end(); ++it)
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
			for(Enemy* enemy : enemies)
			{
				temp = dynamic_cast<Sprite*>(enemy);
				if((*it)->is_player_shot() && (*it)->intersect(temp))
				{
					animations.push_back(new Animation(textures["shot_animation"],
													(*it)->get_left_x(),
													(*it)->get_top_y(),
													256, 32,
													8, 3));
					enemy->decrease_health();
					cout << enemy->get_health() << endl;
					delete *it;
					shots.erase(it);
					return;
				}
			}
			temp = nullptr;

			(*it)->update_pos();
		}
	}
}

void Level::add_to_shots(double x, double y, int w, int h,
				         double angle, int speed, int b,
						 bool player_shot, string text)
{
	shots.push_back(new Shot(x, y, w, h, angle,
							 textures[text],
							 speed, b, player_shot));
}

void Level::enemy_collision_handler()
{
	Sprite* e{nullptr};

	for(Enemy*& enemy : enemies)
	{
		e = dynamic_cast<Sprite*>(enemy);
		if(player->intersect(e))
		{
		player->set_visible(false);
		player->decrease_health();

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

	for(Sprite*& s : level_items)
	{
		if(s->intersect(p))
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
	for(Shot*& s : shots)
	{
		if(s->intersect(p) && s->get_harmless_time() > 20)
		{
			cout << "you ded" << endl;
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

	while (shot->get_bounce_count() >= 0)
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

