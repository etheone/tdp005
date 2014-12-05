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
#include <math.h>

const double PI = 3.14159265;

class Sprite
{
public:
	virtual ~Sprite() = 0;
	Sprite(int x, int y, double angle, const char*& img_file,
			SDL_Renderer*& renderer);

	virtual int get_infront_x();
	virtual int get_infront_y();

	void logSDLError(std::ostream &os, const std::string &msg);
	void loadTexture(SDL_Renderer*& renderer);
	void render_copy(SDL_Renderer*& renderer);
	void set_angle(double new_angle);

	double get_angle();

	void set_position(int x, int y);


protected:
	SDL_Texture* image;
	SDL_Rect rectangle;
	double angle;
	const char* img_file;
};

#endif /* SRC_SPRITE_H_ */







