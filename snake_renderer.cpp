#include "snake_renderer.hpp"
#include <glm/gtx/transform.hpp>

void snake_renderer::update_model(const vec2& pos, float r, float g, float b) const
{
	const auto translation_x = 1.f + (pos.x - snake_instance->field_width / 2) * 2.f;
	const auto translation_y = 1.f + (pos.y - snake_instance->field_height / 2) * 2.f;

	const auto model = glm::translate(glm::mat4(1.f), glm::vec3(translation_y, 0.f, -translation_x));

	glUniformMatrix4fv(model_loc, 1, false, &model[0][0]);
	glUniform3f(color_loc, r, g, b);
}

void snake_renderer::render_cube(const vec2& pos, float r, float g, float b) const
{
	update_model(pos, r, g, b);
	obj_cube.render();

	update_model(pos, 1.f, 1.f, 1.f);
	obj_outline.render();
}

void snake_renderer::render_surface(const vec2& pos, float r, float g, float b) const
{
	update_model(pos, r, g, b);
	obj_surface.render();
}

snake_renderer::snake_renderer(const snake* snake_instance, GLuint program, int width, int height) :
	snake_instance(snake_instance)
{
	const auto projection_loc	= glGetUniformLocation(program, "projection");
	const auto view_loc			= glGetUniformLocation(program, "view");

	model_loc	= glGetUniformLocation(program, "model");
	color_loc	= glGetUniformLocation(program, "input_color");

	const auto projection = glm::perspective(glm::radians(45.f), 
		static_cast<float>(width) / static_cast<float>(height), 0.1f, 1000.f);

	const auto view = glm::lookAt(glm::vec3(45.f, 40.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));

	glUniformMatrix4fv(projection_loc, 1, false, &projection[0][0]);
	glUniformMatrix4fv(view_loc, 1, false, &view[0][0]);

	obj_cube.load();
	obj_surface.load();
	obj_outline.load();
}

void snake_renderer::render() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.15f, 0.15f, 0.15f, 1.f);

	for (int y{}; y < snake_instance->field_height; ++y)
	{
		for (int x{}; x < snake_instance->field_width; ++x)
			render_surface(vec2{x, y}, 0.f, 0.3f, 1.f);
	}

	render_cube(snake_instance->food, 1.f, 0.f, 0.f);
	render_cube(snake_instance->head, 0.6f, 0.f, 1.f);

	for (const auto& tail_pos : snake_instance->tail)
		render_cube(tail_pos, 0.4f, 0.8f, 0.0f);
}