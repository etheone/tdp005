/*
 *  Wall class declaration
 */
#ifndef WALL_H
#define WALL_H

#include "Sprite.h"

//! A simple wall
/*!
 	 It is an image, with substance.
 */
class Wall : public Sprite
{

public:
	Wall(const double& x, const double& y, const int& width,
		 const int& height, SDL_Texture*& texture);
	~Wall();

	void render_copy(SDL_Renderer*& renderer);
};

#endif
