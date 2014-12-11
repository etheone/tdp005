#include "wall.h"

using namespace std;

Wall::Wall(double x, double y, int width, int height, SDL_Texture*& texture)
		: Sprite(x, y, width, height, 0, texture)
{
}

Wall::~Wall()
{
}

void Wall::render_copy(SDL_Renderer*& renderer)
{
	Image::render_copy(renderer);
}

