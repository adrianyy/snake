#pragma once
#include "object.hpp"

class cube
{
	object gl_object;

public:
	void load();
	void render() const;
};