/*
 * HighscoreMenu.h
 *
 *  Created on: 15 dec 2014
 *      Author: joagy323
 */

#ifndef SRC_HIGHSCOREMENU_H_
#define SRC_HIGHSCOREMENU_H_

#include "AbstractGamestate.h"

#include <map>
#include <vector>
#include <string>

#include <fstream>
#include <sstream>

//! Hihghscore_Menu, derived from Abstract_Gamestate
/*!
	Handles reading from, and writing to the specified
	highscore file (.txt).
	It also renderers the score data to the screen with
	the run() method.
*/
class Highscore_Menu : public Abstract_Gamestate
{
public:
	Highscore_Menu(SDL_Renderer*& renderer, std::string file);
	virtual ~Highscore_Menu();

	//! Renders a "add_score" menu interface.
	/*!
		A loop that renders a menu that handles keyboard text input from
		the user. It is interupted by the click of a button and then
		proceeds with overwriting the highscore file with the newly
		received data.
	*/
	void add_score(int time, double accuracy);

	//! Renders a highscore list interface.
	/*!
		A loop that renders a menu that lists the top scores
		read from file. Is interupted by the klick of a button.
	 */
	std::string run();

private:
	std::string highscore_file;

	std::vector< std::pair<std::string, std::string> > scores;
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, Button*> buttons;

	void handle_inputs();

	void read_from_file();
	void overwrite_file();
	void draw_score_list();
	void draw_buttons();
};

#endif /* SRC_HIGHSCOREMENU_H_ */
