#include "Shot.h"

using namespace std;

Shot::Shot(int x, int y, double angle,
		const char*& img_file, int bounce_count,
		int speed, SDL_Renderer*& renderer)
	: Sprite(x, y, angle, img_file, renderer), bounce_count{3}, speed{speed}
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
	exact_x += speed * sin(angle*(PI/180));
	exact_y += speed * -cos(angle*(PI/180));
	rectangle.x = round(exact_x);
	rectangle.y = round(exact_y);
}

void Shot::set_bounce_count(int x)
{
	bounce_count = x;
}

void Shot::reduce_bounce_count()
{
	--bounce_count;
}

int Shot::get_bounce_count()
{
	return bounce_count;
}

int Shot::get_speed()
{
	return speed;
}

void Shot::angle_to_queue(pair<double, double> p, double a)
{
	angles_queue[p] = a;
}
