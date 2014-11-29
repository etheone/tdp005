/*
 * PlayState.h
 *
 *  Created on: 29 nov 2014
 *      Author: joagy323
 */

#ifndef SRC_PLAYSTATE_H_
#define SRC_PLAYSTATE_H_

#include "Player.h"
#include <map>
#include <string>

class Play_State
{
public:
	Play_State(SDL_Renderer*& renderer);
	~Play_State();

	bool play_game();
	void set_up_map();


private:
	SDL_Renderer*& renderer;
	bool running;
	//std::map<std::string, Sprite*> level_items;
	Player* player;
};

#endif /* SRC_PLAYSTATE_H_ */
