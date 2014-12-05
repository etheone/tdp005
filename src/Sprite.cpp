/*
 * Sprite.cpp
 *
 *  Created on: 28 nov 2014
 *      Author: joagy323
 */

#include "Sprite.h"

using namespace std;

Sprite::~Sprite()
{
	// TODO Auto-generated destructor stub
	//SDL_DestroyTexture(image);
}

Sprite::Sprite(int x, int y, double angle, const char*& img_file,
			SDL_Renderer*& renderer)
: image{nullptr}, rectangle({ x, y, 0, 0 }), exact_x{double(x)}, exact_y{double(y)},
  angle{angle}, img_file{img_file}
{
	loadTexture(renderer);
}

void Sprite::logSDLError(std::ostream &os, const std::string &msg)
{
	os << msg << " error: " << SDL_GetError() << std::endl;
}

void Sprite::loadTexture(SDL_Renderer*& renderer)
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

double Sprite::get_angle()
{
	return angle;
}

int Sprite::get_infront_x()
{
	return (rectangle.x + rectangle.w/2)
			+ sin(angle*(PI/180)) * rectangle.w/2;
}

int Sprite::get_infront_y()
{
	return (rectangle.y + rectangle.h/2)
			+ -cos(angle*(PI/180)) * rectangle.h/2;
}

double Sprite::get_exact_x() const
{
	return exact_x;
}

double Sprite::get_exact_y() const
{
	return exact_y;
}

double Sprite::get_exact_bottom_y() const
{
	return exact_y + rectangle.h;
}

double Sprite::get_exact_right_x() const
{
	return exact_x + rectangle.w;
}

double Sprite::get_half_height()
{
	return rectangle.h/2;
}

double Sprite::get_half_width()
{
	return rectangle.w/2;
}

void Sprite::render_copy(SDL_Renderer*& renderer)
{
	SDL_RenderCopyEx(renderer, image, nullptr, &rectangle,
					angle, nullptr, SDL_FLIP_HORIZONTAL);
}

void Sprite::set_angle(double new_angle)
{
	angle = new_angle;
}

void Sprite::set_position(double x, double y)
{
	exact_x = x;
	exact_y = y;
	rectangle.x = round(exact_x);
	rectangle.y = round(exact_y);
}

bool Sprite::intersect(Sprite*& s) const
{
	bool check_y1 {s->get_exact_y() < exact_y + rectangle.h};
	bool check_x1 {s->get_exact_x() < exact_x + rectangle.w};
	bool check_y2 {s->get_exact_bottom_y() > exact_y};
	bool check_x2 {s->get_exact_right_x() > exact_x};

	return check_y1 && check_x1 && check_y2 && check_x2;
}

