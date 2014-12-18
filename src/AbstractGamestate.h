/*
 * AbstractGamestate.h
 *
 *  Created on: 5 dec 2014
 *      Author: joagy323
 */

#ifndef SRC_ABSTRACTGAMESTATE_H_
#define SRC_ABSTRACTGAMESTATE_H_

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Button.h"

//! An abstract "state" class.
/*!
This class stores all things every state have in common,
such as a reference to the SDL_Renderer, the string "gamestate"
and necessary members and method for rendering simple text
to the game-screen
*/
class Abstract_Gamestate
{
public:
	Abstract_Gamestate(SDL_Renderer*& renderer,
			const std::string& gamestate);
	virtual ~Abstract_Gamestate()=0;

	virtual std::string run() = 0;

protected:
	bool running;
	SDL_Renderer* renderer;
	std::string gamestate;

	TTF_Font* font;
	SDL_Color text_color;
	SDL_Rect text_rect;
	SDL_Texture* temp_score;

	//! Creates and renders the text message to the screen.
	/*!
	The texture is also destroyed here, after being rendered.
	*/
	void load_temporary_texture(std::string message, int x, int y);
};

#endif /* SRC_ABSTRACTGAMESTATE_H_ */
