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

class Abstract_Gamestate
{
public:
	Abstract_Gamestate(SDL_Renderer*& renderer);
	virtual ~Abstract_Gamestate()=0;

	virtual void run() = 0;

protected:
	SDL_Renderer* renderer;
};

#endif /* SRC_ABSTRACTGAMESTATE_H_ */
