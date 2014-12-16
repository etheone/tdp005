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
#include "Button.h"
#include <fstream>
#include <sstream>

class Highscore_Menu : public Abstract_Gamestate
{
public:
	Highscore_Menu(SDL_Renderer*& renderer, std::string file);
	virtual ~Highscore_Menu();
	void draw_score_list();

	void add_score(int time, double accuracy);

	std::string run();
	void read_from_file();

private:
	std::string highscore_file;

	TTF_Font* font;
	SDL_Color textColor;
	SDL_Rect renderQuad;
	SDL_Texture* temp_score;
	void handle_inputs();



	std::vector< std::pair<std::string, std::string> > scores;
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, Button*> buttons;

	void load_temporary_texture(std::string message, int x, int y);
};

#endif /* SRC_HIGHSCOREMENU_H_ */
