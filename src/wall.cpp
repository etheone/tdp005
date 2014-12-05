#include "wall.h"


Wall::Wall(int x, int y, double angle, const char*& img_file)
		: Sprite(x, y, angle, img_file)
{

}

Wall::~Wall()
{

	if (image != nullptr)
		{
		SDL_DestroyTexture(image);
		image = nullptr;
		}
	img_file = nullptr;
}

