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
#include <algorithm>
#include <vector>
#include <cmath>
#include <map>

const double PI = 3.14159265;

class Sprite
{
public:
	virtual ~Sprite() = 0;
	Sprite(int x, int y, double angle, const char*& img_file,
			SDL_Renderer*& renderer);

	int get_infront_x();
	int get_infront_y();
	double get_angle();
	double get_exact_x() const;
	double get_exact_y() const;
	double get_exact_bottom_y() const;
	double get_exact_right_x() const;

	double get_half_width();
	double get_half_height();


	void logSDLError(std::ostream &os, const std::string &msg);
	void loadTexture(SDL_Renderer*& renderer);
	virtual void render_copy(SDL_Renderer*& renderer);
	void set_angle(double new_angle);

	bool intersect(Sprite*&) const;

	void set_position(double x, double y);


protected:
	SDL_Texture* image;
	SDL_Rect rectangle;

	// Gives very accurate double coordinates for top_left.
	double exact_x;
	double exact_y;

	double angle;
	const char* img_file;
};

#endif /* SRC_SPRITE_H_ */







