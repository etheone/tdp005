/*
 * Sprite.cpp
 *
 *  Created on: 28 nov 2014
 *      Author: joagy323
 */

#include "Sprite.h"

using namespace std;

Sprite::~Sprite()
{
}

Sprite::Sprite(const double& x, const double& y, const int& width, const int& height,
				const double& angle, SDL_Texture*& texture)
: Image{x, y, width, height, texture}, angle{angle}
{
}

double Sprite::get_angle() const
{
	return angle;
}

double Sprite::get_left_x() const
{
	return exact_x;
}

double Sprite::get_top_y() const
{
	return exact_y;
}

double Sprite::get_bottom_y() const
{
	return exact_y + rectangle.h;
}

double Sprite::get_right_x() const
{
	return exact_x + rectangle.w;
}

double Sprite::get_middle_x() const
{
	return exact_x + get_half_width();
}

double Sprite::get_middle_y() const
{
	return exact_y + get_half_height();
}

double Sprite::get_half_height() const
{
	return rectangle.h/2;
}

double Sprite::get_half_width() const
{
	return rectangle.w/2;
}

void Sprite::set_angle(const double& new_angle)
{
	angle = new_angle;
}

void Sprite::set_position(const double& x, const double& y)
{
	exact_x = x;
	exact_y = y;
	rectangle.x = round(exact_x);
	rectangle.y = round(exact_y);
}

void Sprite::increase_width(const int& increase)
{
	rectangle.w += increase;
}

void Sprite::increase_height(const int& increase)
{
	rectangle.h += increase;
}

void Sprite::render_copy(SDL_Renderer*& renderer)
{
	if(visible)
	{
	SDL_RenderCopyEx(renderer, image, nullptr, &rectangle,
			angle, nullptr ,SDL_FLIP_HORIZONTAL);
	}
}

bool Sprite::intersect(Sprite*& s) const
{
	bool check_y1 {s->get_top_y() <= get_bottom_y()};
	bool check_x1 {s->get_left_x() <= get_right_x()};
	bool check_y2 {s->get_bottom_y() >= get_top_y()};
	bool check_x2 {s->get_right_x() >= get_left_x()};

	return check_y1 && check_x1 && check_y2 && check_x2;
}
