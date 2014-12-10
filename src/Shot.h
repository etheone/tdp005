
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
	Shot(double x, double y, double angle,
		const char*& img_file, int bounce_count,
		int speed, SDL_Renderer*& renderer );
	~Shot();

	void angle_to_queue(std::pair<double, double>, double a);

	void reduce_bounce_count();
	void set_bounce_count(int x);

	int get_bounce_count() const;
	int get_speed() const;
	int get_harmless_time() const;
	std::pair<double, double> get_previous_position() const;

	bool outside_screen() const;
	bool check_left_short_side_collision(Sprite*& s) const;
	bool check_right_short_side_collision(Sprite*& s) const;

	void move_back();
	void update_pos();
	void update_pos_simulation();

private:
	std::map<std::pair<double, double>, double> angles_queue;
	int bounce_count;
	int speed;
	int harmless_time;
	std::pair<double, double> previous_position;

};

#endif /* SRC_SHOT_H_ */
