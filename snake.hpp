#pragma once
#include "vec2.hpp"
#include <vector>

class snake
{
	friend class snake_renderer;

	vec2 velocity, cached_velocity;
	vec2 head, food;

	std::vector<vec2> tail;

	int			tail_count{};
	const int	field_width{};
	const int	field_height{};
	
	vec2 get_random_vec() const;
	bool intersects_with_tail(const vec2& pos) const;
	void handle_collision();

public:
	snake(int field_width, int field_height);

	void update();
	void change_velocity(const vec2& new_velocity);

	int get_score() const;
};