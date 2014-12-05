
/*
 * Shot.h
*/

#ifndef SRC_SHOT_H_
#define SRC_SHOT_H_

#include "Sprite.h"
#include <map>

class Shot : public Sprite
{
public:
	Shot(int x, int y, double angle,
		const char*& img_file, int bounce_count,
		int speed, SDL_Renderer*& renderer );
	~Shot();

	void angle_to_queue(std::pair<double, double>, double a);
	void reduce_bounce_count();

	void set_bounce_count(int x);
	int get_bounce_count();
	int get_speed();

	void update_pos();

private:
	std::map<std::pair<double, double>, double> angles_queue;
	int bounce_count;
	int speed;

};

#endif /* SRC_SHOT_H_ */
