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

class Image {
public:
	Image(double x, double y, SDL_Renderer*& renderer, const char*& img_file);
	virtual ~Image()=0;

	void load_texture(SDL_Renderer*& renderer);
	virtual void render_copy(SDL_Renderer*& renderer);

	void logSDLError(std::ostream &os, const std::string &msg);


protected:
	SDL_Texture* image;
	SDL_Rect rectangle;

	// Gives very accurate "double coordinates"
	//for top-left corner.
	double exact_x;
	double exact_y;

	const char* img_file;
};

#endif /* SRC_IMAGE_H_ */
