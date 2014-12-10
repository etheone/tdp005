/*
 * Enemy.cpp
 */

#include "Enemy.h"

Enemy::Enemy(double x, double y, int width, int height,
		double angle, SDL_Texture*& texture, int health)
: Player(x, y, width, height, angle, texture, health)
{
	// TODO Auto-generated constructor stub
}

Enemy::~Enemy()
{
}
