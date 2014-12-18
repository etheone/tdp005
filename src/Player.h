/*
 * Player.h
 *
 *  Created on: 28 nov 2014
 *      Author: joagy323
 */

#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

#include "Sprite.h"

//! Player class
/*!
 	 Represents a player. Basically a sprite with health.
 	 Most of it's other functionality is handled in the playstate
 	 class.
 */
class Player : public Sprite
{
public:
	Player(const double& x, const double& y,
		   const int& width, const int& height,
		   const double& angle, SDL_Texture*& texture,
		   const int& health);
	~Player();

	int get_health() const;

	void decrease_health();

private:
	int health;
};

#endif /* SRC_PLAYER_H_ */
