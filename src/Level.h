/*
 * Level.h
 *
 *  Created on: 10 dec 2014
 *      Author: joagy323
 */

#ifndef SRC_LEVEL_H_
#define SRC_LEVEL_H_

#include <map>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Level
{
public:
	Level(SDL_Renderer*& renderer);
	virtual ~Level();

	std::map<std::string, SDL_Texture*> textures;



private:
};

#endif /* SRC_LEVEL_H_ */
