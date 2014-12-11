/*
 * Sprite.h
 *
 *  Created on: 28 nov 2014
 *      Author: joagy323
 */

#ifndef SRC_SPRITE_H_
#define SRC_SPRITE_H_

#include "Image.h"

#include <vector>
#include <cmath>
#include <map>

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;

const double PI = 3.14159265;

class Sprite : public Image
{
public:
	virtual ~Sprite() = 0;
	Sprite(double x, double y, int width, int height,
			double angle, SDL_Texture*& texture);

	double get_angle() const;

	double get_left_x() const;
	double get_top_y() const;
	double get_bottom_y() const;
	double get_right_x() const;

	double get_middle_x() const;
	double get_middle_y() const;

	double get_half_width() const;
	double get_half_height() const;

	virtual bool intersect(Sprite*&) const;
	virtual void render_copy(SDL_Renderer*& renderer);

	void set_angle(double new_angle);
	void set_position(double x, double y);


protected:
	double angle;
	bool short_side;
};

#endif /* SRC_SPRITE_H_ */







