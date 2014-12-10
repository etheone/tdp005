/*
 * Player.cpp
 *
 *  Created on: 28 nov 2014
 *      Author: joagy323
 */

#include "Player.h"

Player::Player(double x, double y, int width, int height,
		double angle, SDL_Texture*& texture, int health)
: Sprite(x, y, width, height, angle, texture), health{1}
{
}

Player::~Player()
{
}

int Player::get_health()
{
	return health;
}



