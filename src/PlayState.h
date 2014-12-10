/*
 * PlayState.h
 *
 *  Created on: 29 nov 2014
 *      Author: joagy323
 */

#ifndef SRC_PLAYSTATE_H_
#define SRC_PLAYSTATE_H_

#include "AbstractGamestate.h"
#include "wall.h"
#include "Shot.h"
#include "Animation.h"
#include "Enemy.h"
#include "Level.h"

class Play_State : public Abstract_Gamestate
{
public:
	Play_State(SDL_Renderer*& renderer);
	~Play_State();

	bool play_game();
	void run_game_loop();

	void handle_inputs();

	void set_up_level();
	void draw_level();

	void simulate_shot_path(Shot*& shot);
	void update_shots();

	void player_collision_handler();


private:
	void enemy_collision_handler();

	bool running;

	//handle input stuff
	bool space_down;
	double diff_x;
	double diff_y;
	int angle_wait;
	bool pause;

	std::vector<Sprite*> level_items;
	std::vector<Shot*> shots;
	std::vector<Animation*> animations;
	Player* player;
	Sprite* enemy;
	Level* level;
};

#endif /* SRC_PLAYSTATE_H_ */
