/*
 * Gameengine.h
 *
 *  Created on: 27 nov 2014
 *      Author: joagy323
 */
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


#ifndef SRC_GAMEENGINE_H_
#define SRC_GAMEENGINE_H_

class Game_Engine {
public:
	Game_Engine();
	virtual ~Game_Engine();

	void logSDLError(std::ostream& os, const std::string& msg);

	SDL_Texture* loadTexture(int& pictureWidth,	int& pictureHeight,
							const char*& file, SDL_Renderer *renderer);


private:
};

#endif /* SRC_GAMEENGINE_H_ */
