/*
 * Menu.h
 *
 *  Created on: 11 dec 2014
 *      Author: joagy323
 */

#ifndef SRC_MENU_H_
#define SRC_MENU_H_

#include "AbstractGamestate.h"
#include <map>

//! A menu screen
/*!
 	 Responsible for drawing a menu screen filled with clickable
 	 buttons that redirects the player to another state.
 */
class Menu : public Abstract_Gamestate
{
public:
	Menu(SDL_Renderer*& renderer);
	~Menu();

	std::string run();

private:
	void handle_inputs();
	void draw_menu();

	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, Button*> buttons;
};

#endif /* SRC_MENU_H_ */
