/*
 * Player.cpp
 *
 *  Created on: 28 nov 2014
 *      Author: joagy323
 */

#include "Player.h"

Player::Player(int x, int y) : Sprite(x, y)
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

double Player::get_half_height()
{
	return rectangle.h/2;
}

double Player::get_half_width()
{
	return rectangle.w/2;
}

int Player::get_x()
{
	return rectangle.x;
}

int Player::get_y()
{
	return rectangle.y;
}

void Player::set_new_position(int x, int y)
{
rectangle.x = x;
rectangle.y = y;
}


