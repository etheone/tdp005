
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
		const char*& img_file, int bounce_count,
		int speed, SDL_Renderer*& renderer );
	~Shot();

	int get_height();

	int get_width();
	//returns middle-point x_value
	int get_x();
	//returns middle-point y value
	int get_y();

	int get_bounce_count();

	void update_pos();

private:
	int bounce_count;
	int speed;

};

#endif /* SRC_SHOT_H_ */
