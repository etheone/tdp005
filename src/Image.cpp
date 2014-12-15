/*
 * Image.cpp
 *
 *  Created on: 8 dec 2014
 *      Author: joagy323
 */

#include "Image.h"

Image::Image(const double& x, const double& y, const int& width,
			 const int& height, SDL_Texture*& texture)
: image{texture}, rectangle({int(round(x)), int(round(y)), width, height}),
  exact_x{x}, exact_y{y}, visible{true}
{
	if (image == nullptr)
	{
		logSDLError(std::cerr, "CreateTextureFromSurface");
	}
}

Image::~Image()
{
}

void Image::render_copy(SDL_Renderer*& renderer)
{
	if (visible)
	{
		SDL_RenderCopy(renderer, image, nullptr, &rectangle);
	}
}

void Image::logSDLError(std::ostream &os, const std::string &msg)
{
	os << msg << " error: " << SDL_GetError() << std::endl;
}

void Image::set_visible(const bool& v)
{
	visible = v;
}

bool Image::get_visible()
{
	return visible;
}
