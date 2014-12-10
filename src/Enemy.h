/*
 * Enemy.h
 */

#ifndef SRC_ENEMY_H_
#define SRC_ENEMY_H_
#include "Player.h"

class Enemy : public Player
{
public:
	Enemy(int x, int y, double angle, const char*& img_file,
			SDL_Renderer*& renderer, int health);
	~Enemy();


private:

};

#endif /* SRC_ENEMY_H_ */
