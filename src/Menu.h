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
#include "Button.h"

class Menu : public Abstract_Gamestate
{
public:
	Menu(SDL_Renderer*& renderer);
	~Menu();


private:
	void Menu::draw_menu();
	void run();

	bool running;

	std::map<std::string, SDL_Texture*&> textures;
	std::map<std::string, Button*> buttons;
};

#endif /* SRC_MENU_H_ */
