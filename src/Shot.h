
/*
 * Shot.h
*/

#ifndef SRC_SHOT_H_
#define SRC_SHOT_H_

#include "Sprite.h"
#include "wall.h"


//! Shot class
/*!
 	 Derived from sprite with a lot of extra functionality.
 	 Other than the members inherited from sprite it also has
 	 speed and bounce count.
 */
class Shot : public Sprite
{
public:
	Shot(const double& x, const double& y,
		const int& width, const int& height,
		const double& angle, SDL_Texture*& texture,
		const int& speed, const int& bounce_count, const bool& player_shot);
	~Shot();

	void angle_to_queue(std::pair<double, double>, double a);

	void reduce_bounce_count();
	void set_bounce_count(const int& x);

	int get_bounce_count() const;
	int get_speed() const;
	int get_harmless_time() const;
	bool is_player_shot() const;

	double calculate_angle_update(Sprite*&);

	bool outside_screen() const;

	void move_back();

	void update_pos();
	void update_pos_simulation();

private:
	int bounce_count;
	const int speed;
	int harmless_time;
	bool player_shot;

	std::pair<double, double> previous_position;
	std::vector<std::pair< std::pair< double, double >, double > > angles_queue;

	std::pair<double, double> find_collision_point(Sprite*&);
	void update_position_inner();
};

#endif /* SRC_SHOT_H_ */
