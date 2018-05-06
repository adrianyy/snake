#include "object.hpp"

object::~object()
{
	if (!loaded)
		return;

	glDeleteBuffers(1, &vbo_vertices);
	glDeleteBuffers(1, &vbo_indices);
	glDeleteVertexArrays(1, &vao);
}

void object::load(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices)
{
	indices_count	= indices.size();
	loaded			= true;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo_vertices);
	glGenBuffers(1, &vbo_indices);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, true, 0, nullptr);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void object::render(GLenum draw_mode) const
{
	if (!loaded)
		return;

	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);

	glDrawElements(draw_mode, static_cast<GLsizei>(indices_count), GL_UNSIGNED_INT, nullptr);

	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}
