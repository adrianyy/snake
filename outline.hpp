#pragma once
#include "object.hpp"

class outline
{
	object gl_object;

public:
	void load();
	void render() const;
};