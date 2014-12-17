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

class Highscore_Menu : public Abstract_Gamestate
{
public:
	Highscore_Menu(SDL_Renderer*& renderer, std::string file);
	virtual ~Highscore_Menu();

	void add_score(int time, double accuracy);

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
