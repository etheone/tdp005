/*
 * PlayState.h
 *
 *  Created on: 29 nov 2014
 *      Author: joagy323
 */

#ifndef SRC_PLAYSTATE_H_
#define SRC_PLAYSTATE_H_

#include "AbstractGamestate.h"
#include "Player.h"
#include "wall.h"
#include "Shot.h"

class Play_State : public Abstract_Gamestate
{
public:
	Play_State(SDL_Renderer*& renderer);
	~Play_State();

	bool play_game();
	void set_up_level();
	void draw_level();
	void simulate_shot_path(Shot*& shot);

	void update_shots();


private:
	bool running;
	std::vector<Wall*> level_items;
	std::vector<Shot*> shots;
	std::vector<Wall*> temp_shot_simulation;
	Player* player;
};

#endif /* SRC_PLAYSTATE_H_ */
