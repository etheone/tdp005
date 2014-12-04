/*
 * PlayState.h
 *
 *  Created on: 29 nov 2014
 *      Author: joagy323
 */

#ifndef SRC_PLAYSTATE_H_
#define SRC_PLAYSTATE_H_

#include "Player.h"
#include "wall.h"
#include <vector>
#include <string>

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;

class Play_State
{
public:
	Play_State(SDL_Renderer*& renderer);
	~Play_State();

	bool play_game();
	void set_up_level();
	void draw_level();


private:
	SDL_Renderer*& renderer;
	bool running;
	std::vector<Sprite*> level_items;
	Player* player;
};

#endif /* SRC_PLAYSTATE_H_ */
