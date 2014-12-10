/*
 * Player.cpp
 *
 *  Created on: 28 nov 2014
 *      Author: joagy323
 */

#include "Player.h"

Player::Player(int x, int y, double angle, const char*& img_file,
		SDL_Renderer*& renderer, int health)
: Sprite(x, y, angle, img_file, renderer), health{1}
{
}

Player::~Player()
{
	if (image != nullptr)
	{
	SDL_DestroyTexture(image);
	image = nullptr;
	}
}
void Player::render_copy(SDL_Renderer*& renderer)
{
	Sprite::render_copy(renderer);
}

int Player::get_health()
{
	return health;
}



