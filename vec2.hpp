#pragma once

class vec2
{
public:
	int x{};
	int y{};

	bool operator==(const vec2& vec) const;
	void clear();
};