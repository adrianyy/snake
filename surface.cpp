#include "surface.hpp"
#include <vector>

const static std::vector<GLfloat> vertex_buffer
{
	-1.f, -1.f, 1.f,
	1.f, -1.f, 1.f,
	1.f, -1.f, -1.f,
	-1.f, -1.f, -1.f,
	-1.f, -1.f, 1.f,
};

const static std::vector<GLuint> index_buffer
{
	0, 1,
	1, 2,
	2, 3,
	3, 4,
	4, 0
};

void surface::load()
{
	gl_object.load(vertex_buffer, index_buffer);
}

void surface::render() const
{
	gl_object.render(GL_LINES);
}
