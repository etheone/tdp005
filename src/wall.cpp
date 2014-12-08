#include "wall.h"

using namespace std;

Wall::Wall(int x, int y, double angle, const char*& img_file,
		SDL_Renderer*& renderer)
		: Sprite(x, y, angle, img_file, renderer)
{
	// Calculates the almost exact position for the rotated middle_point
	// necessary for drawing texture.
	if(angle == 0 || angle == 90)
	{
		//do nothing;
	}
	else
	{

	exact_x = rectangle.x + sin(angle*(PI/180)) * rectangle.h/2;
	exact_y = rectangle.y + -sin(angle*(PI/180)) * rectangle.h/2;
	rectangle.x = round(exact_x);
	rectangle.y = round(exact_y);

	// Adds squares with size width*width to the vector,
	// but only the top left_corner for each.
	double left_x{exact_x + (rectangle.h/2 - rectangle.w) * sin(angle*(PI/180))};
	double top_y{exact_y + rectangle.h/2 * sin(angle*(PI/180))};
	for (int i{0}; i < rectangle.h; i += rectangle.w)
	{
		box_container.push_back(make_pair(left_x, top_y));
		left_x += rectangle.w * -sin(angle*(PI/180));
		top_y += rectangle.w * cos(angle*(PI/180));
	}

	// Prints out, for debugging purpose.
	for(pair<double, double>& p : box_container)
	{
		cout << p.first << ", " << p.second << endl;
	}
	}
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
std::vector< std::pair<double, double> > Wall::get_box_container()
{
	return box_container;
}

void Wall::render_copy(SDL_Renderer*& renderer)
{
	SDL_RenderCopy(renderer, image, nullptr, &rectangle);
}
