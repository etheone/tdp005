#include "Shot.h"


Shot::Shot(int x, int y, double angle, const char*& img_file, bounce_count, speed)
//		: Sprite(x, y, angle, img_file), bounce_count{0}, speed{0}
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

int Shot::get_x()
{
	return rectangle.x;
}

int Shot::get_y()
{
	return rectangle.y;
}

