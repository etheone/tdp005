/*
 * PlayState.h
 *
 *  Created on: 29 nov 2014
 *      Author: joagy323
 */

#ifndef SRC_PLAYSTATE_H_
#define SRC_PLAYSTATE_H_

#include "AbstractGamestate.h"
#include "Level.h"

class Play_State : public Abstract_Gamestate
{
public:
	Play_State(SDL_Renderer*& renderer);
	~Play_State();

	std::string run();
	void run_game_loop();
	void clear_play_state();


	void handle_inputs();

private:
	int score;

	bool running;

	Level* level;
	int current_level;


	bool space_down;
	double diff_x;
	double diff_y;
	int angle_wait;
	bool pause;
};

#endif /* SRC_PLAYSTATE_H_ */
