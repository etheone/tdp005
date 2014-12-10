/*
 * Animation.cpp
 *
 *  Created on: 8 dec 2014
 *      Author: joagy323
 */

#include "Animation.h"

using namespace std;

Animation::Animation(SDL_Texture*& texture, const double& x, const double& y,
				const int& width, const int& height,
				const int& frames, const int& updates)
:Image(x, y, width, height, texture),updates_per_frame{updates}, frames{frames},
 frame{0}, updates_to_go{updates}, alive{true}
{
	rectangle.w /= frames;
	rectangle.x = exact_x - rectangle.w/2;
	rectangle.y = exact_y - rectangle.h/2;
	animation_rect.x = 0;
	animation_rect.y = 0;
	animation_rect.w = rectangle.w;
	animation_rect.h = rectangle.h;
}

Animation::~Animation()
{
}

bool Animation::is_alive()
{
	return alive;
}

void Animation::update()
{
	if (updates_to_go == 0)
	{
		updates_to_go = updates_per_frame;
		++frame;
		if (frame == frames)
		{
			frame = 0;
			alive = false;
		}
		animation_rect.x = animation_rect.w * frame;
	}
	else
	{
		--updates_to_go;
	}
}

void Animation::render_copy(SDL_Renderer*& renderer)
{
	SDL_RenderCopy(renderer, image, &animation_rect, &rectangle);
}

