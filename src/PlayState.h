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
#include <vector>

class Play_State : public Abstract_Gamestate
{
public:
	Play_State(SDL_Renderer*& renderer);
	~Play_State();

	bool play_game();
	void set_up_level();
	void draw_level();


private:
	bool running;
	std::vector<Sprite*> level_items;
	Player* player;
};

#endif /* SRC_PLAYSTATE_H_ */
