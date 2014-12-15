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

private:
	int current_time;

	bool running;

	Level* level;
	int current_level;

	bool space_down;
	double diff_x;
	double diff_y;
	int angle_wait;
	int shot_fired;
	int shot_hit;

	void run_game_loop();
	void clear_play_state();
	void handle_inputs();
};

#endif /* SRC_PLAYSTATE_H_ */
