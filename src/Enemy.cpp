/*
 * Enemy.cpp
 */

#include "Enemy.h"

Enemy::Enemy(int x, int y, double angle, const char*& img_file, SDL_Renderer*& renderer, int health)
: Player(x, y, angle, img_file, renderer, health)
{
	// TODO Auto-generated constructor stub
}

Enemy::~Enemy()
{
	if (image != nullptr)
	{
	SDL_DestroyTexture(image);
	image = nullptr;
	}
}
