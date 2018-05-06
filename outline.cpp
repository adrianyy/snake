#include "outline.hpp"
#include <vector>

const static std::vector<GLfloat> vertex_buffer
{
	-1.f, -1.f, 1.f,
	1.f, -1.f, 1.f,
	-1.f, 1.f, 1.f,
	1.f, 1.f, 1.f,

	-1.f, -1.f, -1.f,
	1.f, -1.f, -1.f,
	-1.f, 1.f, -1.f,
	1.f, 1.f, -1.f,
};

const static std::vector<GLuint> index_buffer
{
	0, 1,
	1, 5,
	5, 4,
	4, 0,

	0, 2,
	1, 3,
	5, 7,
	4, 6,

	2, 3,
	3, 7,
	7, 6,
	6, 2
};

void outline::load()
{
	gl_object.load(vertex_buffer, index_buffer);
}

void outline::render() const
{
	glDisable(GL_DEPTH_TEST);
	gl_object.render(GL_LINES);
	glEnable(GL_DEPTH_TEST);
}
