/*
 * Enemy.cpp
 */

#include "Enemy.h"

using namespace std;

Enemy::Enemy(const double& x, const double& y,
		  const int& width, const int& height,
		  const double& angle, SDL_Texture*& texture,
		  const int& health)
: Player(x, y, width, height, angle, texture, health), speed{1}, update_counter{0}
{
}

Enemy::~Enemy()
{
}

int Enemy::get_counter() const
{
	return update_counter;
}

void Enemy::update_pos()
{
	exact_x += speed * sin((angle)*(PI/180));
	exact_y += speed * -cos((angle)*(PI/180));

	rectangle.x = round(exact_x);
	rectangle.y = round(exact_y);
}

void Enemy::update(const vector<Sprite*>& walls)
{

	if (update_counter % 10 == 0)
	{
		update_pos();
		if (any_of(walls.begin(), walls.end(),
				[this](Sprite* s){return intersect(s);}))
		{
			angle += 180;
			update_pos();
		}
	}

	if (update_counter == 100)
	{
		// Random is declared here because eclipse can't compile properly otherwise.
		random_device randint;
		uniform_int_distribution<int> distribution(0, 360);
		angle = distribution(randint);
		update_counter = 0;
	}

	++update_counter;
}
