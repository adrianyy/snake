#include "vec2.hpp"

bool vec2::operator==(const vec2& vec) const
{
	return x == vec.x && y == vec.y;
}

void vec2::clear()
{
	x = y = 0;
}
