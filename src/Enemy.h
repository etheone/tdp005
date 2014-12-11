/*
 * Enemy.h
 */

#ifndef SRC_ENEMY_H_
#define SRC_ENEMY_H_
#include "Player.h"
#include <random>
#include <bits/random.h>

class Enemy : public Player
{
public:
	Enemy(double x, double y, int width, int height,
			double angle, SDL_Texture*& texture, int health);
	~Enemy();

	void update();

	int get_counter() const;



private:
	double speed;
	int update_counter;
};

#endif /* SRC_ENEMY_H_ */
