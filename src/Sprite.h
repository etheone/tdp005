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

const double PI = 3.14159265;

//! The superclass for all game-objects.
/*!
 	 Inherits from the image class.
 	 It also contains the member "angle" and overwrites the rendering
 	 function with a new one, which include angle in its calculation and
 	 rotates the texture accordingly.
 */
class Sprite : public Image
{
public:
	virtual ~Sprite() = 0;
	Sprite(const double& x, const double& y, const int& width,
			const int& height, const double& angle,
			SDL_Texture*& texture);

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

	//! Used by all sprites except wall to set the correct new angle.
	void set_angle(const double& new_angle);

	//! Sets the new top left corner position for players, enemies and shots.
	void set_position(const double& x, const double& y);

	void increase_width(const int& increase);
	void increase_height(const int& increase);

protected:
	double angle;
};

#endif /* SRC_SPRITE_H_ */







