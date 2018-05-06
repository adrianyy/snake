#pragma once
#include "object.hpp"

class surface
{
	object gl_object;

public:
	void load();
	void render() const;
};
