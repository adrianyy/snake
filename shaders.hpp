#pragma once
#include <string>
#include <GL/glew.h>

namespace shaders
{
	GLuint link_program(const std::string& fragment_shader, const std::string& vertex_shader);
};