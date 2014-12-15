/*
 * Image.h
 *
 *  Created on: 8 dec 2014
 *      Author: joagy323
 */

#ifndef SRC_IMAGE_H_
#define SRC_IMAGE_H_

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <algorithm>

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 850;

class Image {
public:
	Image(const double& x, const double& y, const int& width,
			const int& height, SDL_Texture*& texture);
	virtual ~Image() = 0;

	virtual void render_copy(SDL_Renderer*& renderer);

	void logSDLError(std::ostream &os, const std::string &msg);

	void set_visible(const bool& v);
	bool get_visible();

protected:
	SDL_Texture*& image;
	SDL_Rect rectangle;

	// Gives very accurate "double" coordinates
	// for top-left corner.
	double exact_x;
	double exact_y;

	bool visible;

	const char* img_file;
};

#endif /* SRC_IMAGE_H_ */
