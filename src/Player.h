/*
 * Player.h
 *
 *  Created on: 28 nov 2014
 *      Author: joagy323
 */

#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_
#include "Sprite.h"

class Player : public Sprite
{
public:
	Player(int x, int y, double angle, const char*& img_file, int health);
	~Player();

	int get_health();
	//returns bottom right x_value
	int get_x();
	//returns bottom right y value
	int get_y();
	int get_half_width();
	int get_half_height();

private:
	int health;

};

#endif /* SRC_PLAYER_H_ */
