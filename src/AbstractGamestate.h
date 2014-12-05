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

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;

class Abstract_Gamestate
{
public:
	Abstract_Gamestate(SDL_Window*& window);
	virtual ~Abstract_Gamestate();

protected:
	SDL_Renderer* renderer;
};

#endif /* SRC_ABSTRACTGAMESTATE_H_ */