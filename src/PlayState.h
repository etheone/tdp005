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
#include "HighscoreMenu.h"

//! Handle's the game logic
/*!
 	 The run() method creates a new level and starts the main loop
 	 which updates every game-object and handles user input appropriately.
 	 This class also interacts with a reference to a highscore object.
 */
class Play_State : public Abstract_Gamestate
{
public:
	Play_State(SDL_Renderer*& renderer, Highscore_Menu*& highscore);
	~Play_State();

	std::string run();

private:
	int current_time;

	Level* level;
	Highscore_Menu*& highscore;
	int current_level;

	bool space_down;
	double diff_x;
	double diff_y;
	int angle_wait;
	int shot_fired;
	int shot_hit;

	bool player_clicked(int x , int y);

	/*!The inner function of the run() method. It contains
	   the actual game-loop and handles updates of the game_objects.
	*/
	void run_game_loop();

	//! Destroys the level object and frees the memory.
	void clear_play_state();

	void handle_inputs();
};

#endif /* SRC_PLAYSTATE_H_ */
