/*
 * Button.cpp
 *
 *  Created on: 11 dec 2014
 *      Author: joagy323
 */

#include "Button.h"

Button::Button(const double& x, const double& y,
		   	   const int& w, const int& h,
			   SDL_Texture*& texture)
: Image{x, y, w, h, texture}
{
}

Button::~Button()
{
}

bool Button::in_button_area(const int& x, const int& y)
{
	return x < rectangle.x + rectangle.w &&
		   x > rectangle.x &&
		   y < rectangle.y + rectangle.h &&
		   y > rectangle.y;
}
