/*
 * Animation.h
 *
 *  Created on: 8 dec 2014
 *      Author: joagy323
 */

#ifndef SRC_ANIMATION_H_
#define SRC_ANIMATION_H_

#include "Image.h"

//! An animation class
/*!
Handles and draws the animation-sheet texture reference.
Information such as position, number of frames in the texture
and desired amount of updates etc, are specified in the constructor
when the object is instantiated.
*/
class Animation : public Image
{
public:
	Animation(SDL_Texture*& texture,
			  const double& x,
			  const double& y,
			  const int& width,
			  const int& height,
			  const int& frames,
			  const int& updates);
	virtual ~Animation();

	void update();
	bool is_alive();
	void render_copy(SDL_Renderer*& renderer);

private:
	SDL_Rect animation_rect;

	const int updates_per_frame;
	const int frames;

	int frame;
	int updates_to_go;

	bool alive;
};

#endif /* SRC_ANIMATION_H_ */
