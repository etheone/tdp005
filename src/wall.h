/*
 *  Wall class declaration
 */
#ifndef WALL_H
#define WALL_H

#include "Sprite.h"

class Wall : public Sprite
{

public:
	Wall(int x, int y, double angle, const char*& img_file,
			SDL_Renderer*& renderer);
	~Wall();

	void render_copy(SDL_Renderer*& renderer);
	bool intersect(Sprite*&) const;

private:
std::vector< std::pair<double, double> > box_container;
};

#endif
