/*
 * Sprite.cpp
 *
 *  Created on: 28 nov 2014
 *      Author: joagy323
 */

#include "Sprite.h"

Sprite::~Sprite()
{
	// TODO Auto-generated destructor stub
//	SDL_DestroyTexture(draft);
}

Sprite::Sprite(int x, int y) : image{nullptr}, rectangle({ x, y, 0, 0 }), angle{0}
{
}

void Sprite::logSDLError(std::ostream &os, const std::string &msg)
{
	os << msg << " error: " << SDL_GetError() << std::endl;
}

void Sprite::loadTexture(const char*& file, SDL_Renderer* renderer)
{
	SDL_Surface* temp_loaded_image = IMG_Load(file);
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
			else {
				logSDLError(std::cerr, "LoadTexture");
			}
}

void Sprite::render_copy(SDL_Renderer* renderer)
{
	SDL_RenderCopyEx(renderer, image, nullptr, &rectangle,
					angle, nullptr, SDL_FLIP_HORIZONTAL);
}

void Sprite::set_angle(double new_angle)
{
	angle = new_angle;
}
