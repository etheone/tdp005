#include "wall.h"

using namespace std;

Wall::Wall(int x, int y, double angle, const char*& img_file,
		SDL_Renderer*& renderer)
		: Sprite(x, y, angle, img_file, renderer)
{
	/*double left_x{rectangle.x + sin(angle*(PI/180)) * rectangle.h/2};
	double top_y{rectangle.y + -cos(angle*(PI/180)) * rectangle.h/2};
	for (int i{0}; i < rectangle.h; i += rectangle.w)
	{
		box_container.push_back(make_pair(left_x, top_y));
		left_x += rectangle.w * -sin(angle*(PI/180));
		left_x += rectangle.h * cos(angle*(PI/180));
	}*/
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

