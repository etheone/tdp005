/*
 * Level.cpp
 *
 *  Created on: 10 dec 2014
 *      Author: joagy323
 */

#include "Level.h"

using namespace std;

Level::Level(SDL_Renderer*& renderer)
:current_level{"1"}, renderer{renderer}
{
	SDL_Surface* temp = IMG_Load("20x20_wall.png");
	textures["wall"] = SDL_CreateTextureFromSurface(renderer,temp);
	SDL_FreeSurface(temp);

	temp = IMG_Load("outer_x_wall.png");
	textures["outer_x"] = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	temp = IMG_Load("outer_y_wall.png");
	textures["outer_y"] = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	temp = IMG_Load("playership.png");
	textures["player"] = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	temp = IMG_Load("player_shot4x4.png");
	textures["shot"] = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	temp = IMG_Load("coin.png");
	textures["coin"] = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);


	player = new Player(40, 400, 40, 40, 0,textures["player"], 1);
	enemies.push_back(new Enemy(20, 20, 40, 40, 90, textures["player"], 25));

	level_items.push_back(new Wall(0, 0, 1200, 15, textures["outer_x"]));
	level_items.push_back(new Wall(0, SCREEN_HEIGHT-15, 1200, 15, textures["outer_x"]));
	level_items.push_back(new Wall(SCREEN_WIDTH-15, 0, 15, 800, textures["outer_y"]));
	level_items.push_back(new Wall(0, 0, 15, 800, textures["outer_y"]));
}

Level::~Level()
{
	delete player;
	player = nullptr;

	for(Sprite*& e : enemies)
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
//Loads a level from a file line by line and adds it to the
//different vectors that contains the objects in the world
	std::map<std::string, char> objects{{"wall", '#'}, {"player", 'p'}, {"enemy", 'e'}};

	string level_str = "levels/level" + current_level + ".txt";
	ifstream file(level_str);
	string line{""};

	for(int line_number{1}; line_number < 40; ++line_number)
	{
		getline(file, line);
		for (unsigned int i{1}; i < 60; ++i)
		{
			if (line[i] == objects["wall"])
			{
				cout << line[i];

				level_items.push_back(new Wall(i*20, line_number*20, 20, 20, textures["wall"]));
			}

//			if (line[i] == objects["player"])
//			{
//				player = new Player(20 ,50 , i*80, current_line*80, *textures["player"]);
//			}

			if (line[i] == objects["enemy"])
			{
				enemies.push_back(new Enemy(i*20, line_number*20, 40, 40, 180, textures["player"], 25));
			}
			/*if (line[i] == objects["lava"])
			{
				enemies.push_back(new Lava(80,80,(i*80),(current_line*80), *textures["lava"]));
			}
			if (line[i] == objects["button"])
			{
				button = new Button(20 ,80 , i*80 + 60, current_line*80, *textures["button"]);
				//enemies.push_back(new Lava(80,80,(i*80),(current_line*80), *textures["lava"]));
			}*/

		}
		cout << endl;

	}
	file.close();
}

void Level::draw_level()
{
	player->render_copy(renderer);

	for (Sprite*& enemy : enemies)
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

void Level::update_shots()
{
	for(vector<Shot*>::iterator it{shots.begin()}; it !=shots.end(); ++it)
	{
		if ((*it)->get_bounce_count() < 0 || (*it)->outside_screen())
		{
			animations.push_back(new Animation(textures["coin"],
								(*it)->get_left_x(),
								(*it)->get_top_y(),
								270, 30,
								9, 20));
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

void Level::add_to_shots(double x, double y, int w, int h,
				  double angle, int speed, int b)
{
	shots.push_back(new Shot(x, y, w, h, angle, textures["shot"], speed, b));
}

void Level::enemy_collision_handler()
{
	for(Sprite*& enemy : enemies)
	{
		if(player->intersect(enemy))
		{
		player->set_visible(false);
		}
	}
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
		}
	}
	for(Shot*& s : shots)
	{
		if(s->intersect(p) && s->get_harmless_time() > 20)
		{
			cout << "you ded" << endl;
		//	pause = true;
			//running = false;
		}
	}
	p = nullptr;
}

// Behövs till fienderna...
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
//				level_items.push_back(new Wall(shot->get_left_x(),
//	            shot->get_top_y(), 4, 4,textures["shot"]));
			}
		}
		shot->update_pos_simulation();
	}
	shot->set_position(temp_x, temp_y);
	shot->set_angle(temp_angle);
	shot->set_bounce_count(temp_bounce_count);
}

//	level_items.push_back(new Wall(500, 500, 20, 20, level->textures["wall"]));

