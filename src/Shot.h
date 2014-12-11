
/*
 * Shot.h
*/

#ifndef SRC_SHOT_H_
#define SRC_SHOT_H_

#include "Sprite.h"
#include "wall.h"

class Shot : public Sprite
{
public:
	Shot(double x, double y,
		int width, int height,
		double angle, SDL_Texture*& texture,
		int speed, int bounce_count, bool player_shot);
	~Shot();

	void angle_to_queue(std::pair<double, double>, double a);

	void reduce_bounce_count();
	void set_bounce_count(int x);

	int get_bounce_count() const;
	int get_speed() const;
	int get_harmless_time() const;
	bool is_player_shot();


	double calculate_angle_update(Sprite*&);

	bool outside_screen() const;

	void move_back();
	void update_pos();
	void update_pos_simulation();

private:
	int bounce_count;
	int speed;
	int harmless_time;
	bool player_shot;

	std::pair<double, double> previous_position;
	std::map<std::pair<double, double>, double> angles_queue;

	std::pair<double, double> find_collision_point(Sprite*&);
	void update_position_inner();
};

#endif /* SRC_SHOT_H_ */
