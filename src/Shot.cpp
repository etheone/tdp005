#include "Shot.h"

using namespace std;

Shot::Shot(double x, double y, double angle,
		const char*& img_file, int bounce_count,
		int speed, SDL_Renderer*& renderer)
	: Sprite(x, y, angle, img_file, renderer), bounce_count{bounce_count},
	  speed{speed}, harmless_time{0}, previous_position{x, y}
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
	++harmless_time;
	for (const pair<pair<double, double>, double>& p :angles_queue)
		{
			if (exact_x == p.first.first && exact_y == p.first.second)
			{
				angle = p.second;
				bounce_count -= 1;
				break;
			}
		}
	rectangle.x = round(exact_x);
	rectangle.y = round(exact_y);
}

void Shot::move_back()
{
	exact_x = previous_position.first;
	exact_y = previous_position.second;

	rectangle.x = round(exact_x);
	rectangle.y = round(exact_y);
}

void Shot::update_pos_simulation()
{
	previous_position = {exact_x, exact_y};
	exact_x += speed * sin(angle*(PI/180));
	exact_y += speed * -cos(angle*(PI/180));

	rectangle.x = round(exact_x);
	rectangle.y = round(exact_y);
}

int Shot::get_harmless_time() const
{
	return harmless_time;
}

void Shot::set_bounce_count(int x)
{
	bounce_count = x;
}

void Shot::reduce_bounce_count()
{
	--bounce_count;
}

int Shot::get_bounce_count() const
{
	return bounce_count;
}

int Shot::get_speed() const
{
	return speed;
}

pair<double, double> Shot::get_previous_position() const
{
	return previous_position;
}

void Shot::angle_to_queue(pair<double, double> p, double a)
{
	angles_queue[p] = a;
}

bool Shot::outside_screen() const
{
	bool check_y{exact_y < 0 || exact_y > SCREEN_HEIGHT-15};
	bool check_x{exact_x < 0 || exact_x > SCREEN_WIDTH-15};

	return check_x || check_y;
}

bool Shot::check_left_short_side_collision(Sprite*& s) const
{
	// Checks if there's a collision between a shot and a walls "left" short side.
	// Only works for walls with angle 90 or 0 degrees.
	bool check_y1;
	bool check_x1;
	bool check_y2;
	bool check_x2;

	if(s->get_angle() == 0)
	{
		check_x1 = previous_position.first + rectangle.w
				> s->get_left_x() - 20;
		check_x2 = previous_position.first
				< s->get_right_x() + 20;
		check_y1 = previous_position.second + rectangle.h
				> s->get_top_y() - 30;
		check_y2 = previous_position.second
				< s->get_top_y();

		return check_y1 && check_x1 && check_y2 && check_x2;
	}
	else if (s->get_angle() == 90)
	{
		check_x1 = previous_position.first + rectangle.w
				> s->get_left_x() - 30;
		check_x2 = previous_position.first
				< s->get_left_x();
		check_y1 = previous_position.second + rectangle.h
				> s->get_top_y() - 20;
		check_y2 = previous_position.second
				< s->get_bottom_y() + 20;

				return check_y1 && check_x1 && check_y2 && check_x2;
	}
	return false;
}

bool Shot::check_right_short_side_collision(Sprite*& s) const
{
	// Checks if there's a collision between a shot and a walls "right" short side.
	// Only works for walls with angle 90 or 0 degrees.
	bool check_y1;
	bool check_x1;
	bool check_y2;
	bool check_x2;

	if(s->get_angle() == 0)
	{
		check_x1 = previous_position.first
				< s->get_right_x() + 20;
		check_x2 = previous_position.first + rectangle.w
				> s->get_left_x() - 20;
		check_y1 = previous_position.second
				< s->get_bottom_y() + 30;
		check_y2 = previous_position.second  + rectangle.h
				> s->get_bottom_y();

		return check_y1 && check_x1 && check_y2 && check_x2;
	}
	else if (s->get_angle() == 90)
	{
		check_x1 = previous_position.first
				< s->get_right_x() + 30;
		check_x2 = previous_position.first + rectangle.w
				> s->get_right_x();
		check_y1 = previous_position.second
				< s->get_bottom_y() + 20;
		check_y2 = previous_position.second + rectangle.h
				> s->get_top_y() - 20;

				return check_y1 && check_x1 && check_y2 && check_x2;
	}
	return false;
}


