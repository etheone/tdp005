/*
 *  Wall class declaration
 */
#ifndef WALL_H
#define WALL_H

#include "Sprite.h"

class Wall : public Sprite
{

public:
	Wall(double x, double y,
		int width, int height,
		SDL_Texture*& texture);
	~Wall();

	void render_copy(SDL_Renderer*& renderer);

private:
std::vector< std::pair<double, double> > box_container;
};

#endif
