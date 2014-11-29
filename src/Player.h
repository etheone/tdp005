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
	Player( int x, int y);
	~Player();

	void set_new_position(int x, int y);
	int get_x();
	int get_y();
	double get_half_width();
	double get_half_height();

private:

};

#endif /* SRC_PLAYER_H_ */
