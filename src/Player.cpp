/*
 * Player.cpp
 *
 *  Created on: 28 nov 2014
 *      Author: joagy323
 */

#include "Player.h"

Player::Player(int x, int y, double angle, const char*& img_file)
: Sprite(x, y, angle, img_file)
{
	// TODO Auto-generated constructor stub
}

Player::~Player()
{
	if (image != nullptr)
	{
	SDL_DestroyTexture(image);
	image = nullptr;
	}
}

int Player::get_half_height()
{
	return rectangle.h/2;
}

int Player::get_half_width()
{
	return rectangle.w/2;
}

int Player::get_x()
{
	return rectangle.x + get_half_width();
}

int Player::get_y()
{
	return rectangle.y + get_half_height();
}



