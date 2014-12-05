#include "Shot.h"

using namespace std;

Shot::Shot(int x, int y, double angle,
		const char*& img_file, int bounce_count,
		int speed, SDL_Renderer*& renderer)
	: Sprite(x, y, angle, img_file, renderer), bounce_count{0}, speed{0}
{
}

Shot::~Shot()
{

	if (image != nullptr)
		{
		SDL_DestroyTexture(image);
		image = nullptr;
		}
	img_file = nullptr;
}

void Shot::update_pos()
{
	rectangle.x += speed * cos(angle*(PI/180) + 90);
	rectangle.y += speed * sin(angle*(PI/180) + 90);
}

int Shot::get_height()
{
	return rectangle.h;
}

int Shot::get_width()
{
	return rectangle.w;
}

int Shot::get_x()
{
	return rectangle.x;
}

int Shot::get_y()
{
	return rectangle.y;
}

int Shot::get_bounce_count()
{
	return bounce_count;
}

