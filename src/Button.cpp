/*
 * Button.cpp
 *
 *  Created on: 11 dec 2014
 *      Author: joagy323
 */

#include "Button.h"

Button::Button(double x, double y, int w, int h, SDL_Texture*& texture)
: Image{x, y, w, h, texture}
{
	// TODO Auto-generated constructor stub
}

Button::~Button()
{
}

bool Button::in_button_area(int x, int y)
{
	return x < rectangle.x + rectangle.w &&
		   x > rectangle.x &&
		   y < rectangle.y + rectangle.h &&
		   y > rectangle.y;
}
