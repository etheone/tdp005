/*
 * Enemy.h
 */

#ifndef SRC_ENEMY_H_
#define SRC_ENEMY_H_
#include "Sprite.h"

class Enemy : public Sprite
{
public:
	Enemy(int x, int y, double angle, const char*& img_file, int health);
	~Enemy();

	//returns bottom right x_value
	int get_x();
	//returns bottom right y value
	int get_y();
	int get_width();
	int get_height();
	int get_health();

private:
	int health;

};

#endif /* SRC_ENEMY_H_ */
