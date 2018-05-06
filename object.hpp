#pragma once
#include <GL/glew.h>
#include <vector>

class object
{
	size_t indices_count{};

	GLuint vao{};
	GLuint vbo_vertices{}, vbo_indices{};
	bool   loaded{};

public:
	~object();

	void load(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices);
	void render(GLenum draw_mode) const;
};