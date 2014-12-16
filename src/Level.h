/*
 * Level.h
 *
 *  Created on: 10 dec 2014
 *      Author: joagy323
 */

#ifndef SRC_LEVEL_H_
#define SRC_LEVEL_H_

#include <map>
#include <iostream>
#include <fstream>
#include "wall.h"
#include "Shot.h"
#include "Animation.h"
#include "Enemy.h"
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Level
{
public:
	Level(SDL_Renderer*& renderer, int& level_time, int& shot_hit);
	virtual ~Level();
	void load_level(const int& level);
	void draw_level();

	void simulate_shot_path();
	void update_shots();
	void update_enemy();
	void update_time();

	void player_collision_handler();

	void add_to_shots(const double& x, const double& y, const int& w,
					  const int& h, const double& angle, const int& speed,
					  const int& b, const bool& player_shot, std::string = "shot");
	void enemy_collision_handler();
	void clear_level();

	bool shots_empty();
	bool no_enemies();

	int get_time() const;


	Player* player;

private:
	int& level_time;
	int& shot_hit;


	std::map<std::string, SDL_Texture*> textures;
	std::vector<Sprite*> level_items;
	std::vector<Shot*> shots;
	std::vector<Animation*> animations;
	std::vector<Enemy*> enemies;

	SDL_Texture* temp_score;
	TTF_Font* font;
	SDL_Color textColor;
	SDL_Rect renderQuad;

	SDL_Renderer*& renderer;
	SDL_Rect back;

	void draw_score();

	bool combine_y_walls(const int& x, const int& y);
};

#endif /* SRC_LEVEL_H_ */
