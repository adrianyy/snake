#include "cube.hpp"
#include <vector>

const static std::vector<GLfloat> vertex_buffer
{
	-1.f, 1.f, -1.f,
	1.f, 1.f, -1.f,
	-1.f, -1.f, -1.f,
	1.f, -1.f, -1.f,

	-1.f, 1.f, 1.f,
	1.f, 1.f, 1.f,
	-1.f, -1.f, 1.f,
	1.f, -1.f, 1.f
};

const static std::vector<GLuint> index_buffer
{
	0, 1, 2,
	2, 1, 3,

	5, 4, 7,
	7, 4, 6,

	1, 5, 3,
	3, 5, 7,

	4, 0, 6,
	6, 0, 2,

	4, 5, 0,
	0, 5, 1,

	2, 3, 6,
	6, 3, 7
};

void cube::load()
{
	gl_object.load(vertex_buffer, index_buffer);
}

void cube::render() const
{
	gl_object.render(GL_TRIANGLES);
}
