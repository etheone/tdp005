/*
 * Player.cpp
 *
 *  Created on: 28 nov 2014
 *      Author: joagy323
 */

#include "Player.h"

Player::Player(double x, double y, int width, int height,
		double angle, SDL_Texture*& texture, int health)
: Sprite(x, y, width, height, angle, texture), health{health}
{
}

Player::~Player()
{
}

int Player::get_health() const
{
	return health;
}

void Player::decrease_health()
{
	--health;
}
