#include "Shot.h"

using namespace std;

Shot::Shot(const double& x, const double& y,
		const int& width, const int& height,
		const double& angle, SDL_Texture*& texture,
		const int& speed, const int& bounce_count, const bool& player_shot)
	: Sprite(x, y, width, height, angle, texture), bounce_count{bounce_count},
	  speed{speed}, harmless_time{0}, player_shot{player_shot}, previous_position{x, y}
{
}

Shot::~Shot()
{
}

void Shot::update_pos()
{
	update_position_inner();
	++harmless_time;
	for (const pair<pair<double, double>, double>& p :angles_queue)
	{
		if (exact_x == p.first.first && exact_y == p.first.second)
		{
			angle = p.second;
			bounce_count -= 1;
		}
	}
}

void Shot::move_back()
{
	exact_x = previous_position.first;
	exact_y = previous_position.second;

	rectangle.x = round(exact_x);
	rectangle.y = round(exact_y);
}

void Shot::update_position_inner()
{
	exact_x += speed * sin(angle*(PI/180));
	exact_y += speed * -cos(angle*(PI/180));

	rectangle.x = round(exact_x);
	rectangle.y = round(exact_y);
}

void Shot::update_pos_simulation()
{
	previous_position = {exact_x, exact_y};
	update_position_inner();

}
bool Shot::is_player_shot() const
{
	return player_shot;
}

int Shot::get_harmless_time() const
{
	return harmless_time;
}

void Shot::set_bounce_count(const int& x)
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

void Shot::angle_to_queue(pair<double, double> p, double a)
{
	angles_queue[p] = a;
}

bool Shot::outside_screen() const
{
	bool check_y{exact_y < -5 || exact_y > SCREEN_HEIGHT+15};
	bool check_x{exact_x < -5 || exact_x > SCREEN_WIDTH+15};

	return check_x || check_y;
}

pair<double, double> Shot::find_collision_point(Sprite*& s)
{
	double temp_x{exact_x};
	double temp_y{exact_y};
	exact_x = previous_position.first;
	exact_y = previous_position.second;

	while (!intersect(s))
	{
		exact_x += sin(angle*(PI/180)) * 0.5;
		exact_y += -cos(angle*(PI/180)) * 0.5;
	}

	pair<double, double> p{exact_x, exact_y};
	exact_x = temp_x;
	exact_y = temp_y;

	return p;
}

// Bounces the shot correctly depending on which side of the wall the shot hits
double Shot::calculate_angle_update(Sprite*& wall)
{
	pair<double, double> collision_point{find_collision_point(wall)};
	if (round(collision_point.first + rectangle.w) == wall->get_left_x() ||
		round(collision_point.first) == wall->get_right_x())
	{
		return -angle;
	}

	return -angle + 180;
}
