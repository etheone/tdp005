#include "wall.h"


Wall::Wall(int x, int y, double angle, const char*& img_file,
		SDL_Renderer*& renderer)
		: Sprite(x, y, angle, img_file, renderer)
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

