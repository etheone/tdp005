/*
 * Player.cpp
 *
 *  Created on: 28 nov 2014
 *      Author: joagy323
 */

#include "Player.h"

Player::Player(const double& x, const double& y,
		   const int& width, const int& height,
		   const double& angle, SDL_Texture*& texture,
		   const int& health)
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
