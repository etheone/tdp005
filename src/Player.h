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
	Player(double x, double y, int width, int height,
			double angle, SDL_Texture*& texture, int health);
	~Player();

	int get_health();

private:
	int health;

};

#endif /* SRC_PLAYER_H_ */
