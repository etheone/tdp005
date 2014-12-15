/*
 * GameScreen.h
 *
 *  Created on: 5 dec 2014
 *      Author: joagy323
 */

#ifndef SRC_GAMESCREEN_H_
#define SRC_GAMESCREEN_H_

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Game_Screen
{
public:
	Game_Screen(const int& screen_width, const int& screen_height);
	virtual ~Game_Screen();

	SDL_Renderer*& get_renderer();

private:
	const int screen_width;
	const int screen_height;

	SDL_Window* window;
	SDL_Renderer* renderer;
};

#endif /* SRC_GAMESCREEN_H_ */
