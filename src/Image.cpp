/*
 * Image.cpp
 *
 *  Created on: 8 dec 2014
 *      Author: joagy323
 */

#include "Image.h"

Image::Image(double x, double y, SDL_Renderer*& renderer, const char*& img_file)
: image{nullptr}, rectangle({int(round(x)), int(round(y)), 0, 0}),
  exact_x{x}, exact_y{y}, visible{true}, img_file{img_file}
{
	load_texture(renderer);
}

Image::~Image() {
	// TODO Auto-generated destructor stub
}

void Image::load_texture(SDL_Renderer*& renderer)
{
	SDL_Surface* temp_loaded_image = IMG_Load(img_file);
	// If the loading went ok, convert to texture and return the texture
	if (temp_loaded_image != nullptr)
	{
		rectangle.w = temp_loaded_image->w;
		rectangle.h = temp_loaded_image->h;
		image = SDL_CreateTextureFromSurface(renderer, temp_loaded_image);
		SDL_FreeSurface(temp_loaded_image);
		// Make sure converting went okay too
		if (image == nullptr)
		{
			logSDLError(std::cerr, "CreateTextureFromSurface");
		}
	}
	else
	{
		logSDLError(std::cerr, "LoadTexture");
	}
}

void Image::render_copy(SDL_Renderer*& renderer)
{
	if(visible)
	{
	SDL_RenderCopy(renderer, image, nullptr, &rectangle);
	}
}

void Image::logSDLError(std::ostream &os, const std::string &msg)
{
	os << msg << " error: " << SDL_GetError() << std::endl;
}

void Image::set_visible(bool v)
{
	visible = v;
}

bool Image::get_visible()
{
	return visible;
}
