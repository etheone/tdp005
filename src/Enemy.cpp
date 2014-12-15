/*
 * Enemy.cpp
 */

#include "Enemy.h"

using namespace std;

Enemy::Enemy(double x, double y, int width, int height,
		double angle, SDL_Texture*& texture, int health)
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
	// Random is declared here because eclipse can't compile properly otherwise.


	if(update_counter == 100)
	{
		random_device randint;
		uniform_int_distribution<int> distribution(0, 360);
		angle = distribution(randint);
		update_counter = 0;
	}
	else if(any_of(walls.begin(), walls.end(),
			[this](Sprite* s){return intersect(s);}))
	{
		angle += 180;
		cout << "collision "<< endl;
		update_pos();
		update_pos();
	}
	else if(update_counter % 10 == 0)
	{
		update_pos();
	}
	++update_counter;
}
