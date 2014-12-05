/*
 * Enemy.cpp
 */

#include "Enemy.h"

Enemy::Enemy(int x, int y, double angle, const char*& img_file, int health)
: Sprite(x, y, angle, img_file), health{0}
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

int Enemy::get_height()
{
	return rectangle.h;
}

int Enemy::get_width()
{
	return rectangle.w;
}

int Enemy::get_x()
{
	return rectangle.x;
}

int Enemy::get_y()
{
	return rectangle.y;
}

int Enemy::get_health()
{
	return health;
}
