#include "Shot.h"

using namespace std;

Shot::Shot(int x, int y, double angle,
		const char*& img_file, int bounce_count,
		int speed, SDL_Renderer*& renderer)
	: Sprite(x, y, angle, img_file, renderer), bounce_count{bounce_count}, speed{speed}
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
	for (const pair<pair<double, double>, double>& p :angles_queue)
		{
			if (exact_x == p.first.first && exact_y == p.first.second)
			{
				angle = p.second;
				bounce_count -= 1;
				exact_x += speed * sin(angle*(PI/180));
				exact_y += speed * -cos(angle*(PI/180));
				break;
			}
		}

	rectangle.x = round(exact_x);
	rectangle.y = round(exact_y);
}

void Shot::update_pos2()
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


bool Shot::intersect(Wall*& w) const
{
	if(angle == 0 || 90)
	{
		bool check_y1 {w->get_exact_y() < exact_y + rectangle.h};
		bool check_x1 {w->get_exact_x() < exact_x + rectangle.w};
		bool check_y2 {w->get_exact_bottom_y() > exact_y};
		bool check_x2 {w->get_exact_right_x() > exact_x};

		return check_y1 && check_x1 && check_y2 && check_x2;
	}
	else{


	bool check_y1;
	bool check_x1;
	bool check_y2;
	bool check_x2;


	for (pair<double, double>& p : w->get_box_container())
	{
		//cout << p.first << "  " << p.second << endl;
		check_y1 = get_exact_y() <= p.second + 15;
		check_x1 = get_exact_x() <= p.first + 15;
		check_y2 = get_exact_bottom_y() >= p.second;
		check_x2 = get_exact_right_x() >= p.first;

		if(check_y1 && check_x1 && check_y2 && check_x2)
		{
			return true;
		}
	}
	return false;
	}
}
