
/*
 * Shot.h
*/

#ifndef SRC_SHOT_H_
#define SRC_SHOT_H_

#include "Sprite.h"

class Shot : public Sprite
{
public:
	Shot(int x, int y, double angle,
		const char*& img_file, int bounce_count, int speed);
	~Shot();

	int get_height();

	int get_width();
	//returns bottom right x_value
	int get_x();
	//returns bottom right y value
	int get_y();

	int get_bounce_count();

private:
	int bounce_count;
	int speed;

};

#endif /* SRC_SHOT_H_ */
