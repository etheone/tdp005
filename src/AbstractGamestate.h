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

	void load_temporary_texture(std::string message, int x, int y);

};

#endif /* SRC_ABSTRACTGAMESTATE_H_ */
