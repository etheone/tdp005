/*
 * Sprite.h
 *
 *  Created on: 28 nov 2014
 *      Author: joagy323
 */

#ifndef SRC_SPRITE_H_
#define SRC_SPRITE_H_

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>



class Sprite
{
public:
	virtual ~Sprite() = 0;
	Sprite(int x, int y);

	void logSDLError(std::ostream &os, const std::string &msg);
	void loadTexture(const char*& file, SDL_Renderer* renderer);
	void render_copy(SDL_Renderer* renderer);
	void set_angle(double new_angle);


protected:
	SDL_Texture* image;
	SDL_Rect rectangle;
	double angle;
};

#endif /* SRC_SPRITE_H_ */







