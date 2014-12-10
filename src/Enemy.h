/*
 * Enemy.h
 */

#ifndef SRC_ENEMY_H_
#define SRC_ENEMY_H_
#include "Player.h"

class Enemy : public Player
{
public:
	Enemy(double x, double y, int width, int height,
			double angle, SDL_Texture*& texture, int health);
	~Enemy();


private:

};

#endif /* SRC_ENEMY_H_ */
