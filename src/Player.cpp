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
	SDL_DestroyTexture(image);
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


