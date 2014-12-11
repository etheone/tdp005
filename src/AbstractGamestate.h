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
	Abstract_Gamestate(SDL_Renderer*& renderer,
			std::string gamestate);
	virtual ~Abstract_Gamestate()=0;

	std::string get_state() const;
	void set_gamestate(std::string str);



	virtual std::string run() = 0;

protected:
	SDL_Renderer* renderer;
	std::string gamestate;
};

#endif /* SRC_ABSTRACTGAMESTATE_H_ */
