#include "snake.hpp"
#include <algorithm>
#include <random>

vec2 snake::get_random_vec() const
{
	static std::random_device rnd;
	static std::uniform_int_distribution<int> dist_x(0, field_width - 1);
	static std::uniform_int_distribution<int> dist_y(0, field_height - 1);

	return vec2{
		dist_x(rnd),
		dist_y(rnd)
	};
}

bool snake::intersects_with_tail(const vec2& pos) const
{
	return std::any_of(tail.begin(), tail.end(), [&pos](const vec2& tail_pos){ return tail_pos == pos; });
}

void snake::handle_collision()
{
	if (intersects_with_tail(head))
	{
		tail.clear();
		velocity.clear();

		head		= get_random_vec();
		tail_count	= 0;
	}

	if (head == food)
	{
		do
		{
			food = get_random_vec();
		} while (food == head || intersects_with_tail(food));

		++tail_count;
	}
}

snake::snake(int field_width, int field_height) :
	field_width(field_width), field_height(field_height)
{
	food = get_random_vec();
	head = get_random_vec();
}

int snake::get_score() const
{
	return tail_count;
}

void snake::update()
{
	velocity = cached_velocity;
	handle_collision();

	for (int i = 0; i < static_cast<long>(tail.size()) - 1; ++i)
		tail[i] = tail[i + 1];

	if (tail_count > 0)
	{
		if (tail_count > tail.size())
			tail.emplace_back(head);
		else
			tail[tail_count - 1] = head;
	}

	head.x += velocity.x;
	head.y += velocity.y;

	if (head.x >= field_width)
		head.x = 0;
	else if (head.x < 0)
		head.x = field_width - 1;

	if (head.y >= field_height)
		head.y = 0;
	else if (head.y < 0)
		head.y = field_height - 1;
}

void snake::change_velocity(const vec2& new_velocity)
{
	if (tail_count > 0)
	{
		if (velocity.x != 0 && velocity.x == -new_velocity.x)
			return;

		if (velocity.y != 0 && velocity.y == -new_velocity.y)
			return;
	}

	cached_velocity = std::move(new_velocity);
}