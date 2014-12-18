/*
 * Enemy.h
 */

#ifndef SRC_ENEMY_H_
#define SRC_ENEMY_H_

#include "Player.h"
#include <random>
#include <bits/random.h>

//! An enemy class
/*!
	Derived from player. Their movement speed is predefined
	and constant. Their angle is randomly updated, but in
	a constant and defined time interval.
*/
class Enemy : public Player
{
public:
	Enemy(const double& x, const double& y,
		  const int& width, const int& height,
		  const double& angle, SDL_Texture*& texture,
		  const int& health);
	~Enemy();

	//! Updates the enemy
	/*!
	 	 Randomized angle changing and position update.
	 	 If it ends up in a wall, it will turn around a 180
	 	 degrees and then move away from it.
	 */
	void update(const std::vector<Sprite*>& walls);
	void update_pos();

	int get_counter() const;

private:
	const double speed;
	int update_counter;
};

#endif /* SRC_ENEMY_H_ */
