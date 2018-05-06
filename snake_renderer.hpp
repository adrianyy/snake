#pragma once
#include "outline.hpp"
#include "surface.hpp"
#include "cube.hpp"
#include "snake.hpp"

#include <glm/glm.hpp>

class snake_renderer
{
	const snake* snake_instance;

	GLint		 model_loc;
	GLint		 color_loc;

	cube		 obj_cube;
	surface		 obj_surface;
	outline		 obj_outline;

	void update_model(const vec2& pos, float r, float g, float b) const;
	void render_cube(const vec2& pos, float r, float g, float b) const;
	void render_surface(const vec2& pos, float r, float g, float b) const;

public:
	snake_renderer(const snake* snake_instance, GLuint program, int width, int height);

	void render() const;
};