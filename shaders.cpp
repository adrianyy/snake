#include "shaders.hpp"
#include <windows.h>
#include <fstream>
#include <sstream>
#include <vector>

static std::string get_file(const std::string& path)
{
	std::ifstream file(path);
	std::stringstream stream;

	if (file)
		stream << file.rdbuf();

	return std::move(stream.str());
}

static GLuint compile_shader(const std::string& path, GLenum type)
{
	const auto source_str	= get_file(path);
	const auto source		= source_str.c_str();
	const auto shader		= glCreateShader(type);

	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	GLint length{};
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

	if (length > 0)
	{
		std::vector<char> message(length + 1);
		glGetShaderInfoLog(shader, length, nullptr, message.data());

		MessageBoxA(nullptr, message.data(), path.data(), MB_OK);
		std::exit(-1);
	}

	return shader;
}

GLuint shaders::link_program(const std::string& fragment_shader, const std::string& vertex_shader)
{
	const auto frag		= compile_shader(fragment_shader, GL_FRAGMENT_SHADER);
	const auto vert		= compile_shader(vertex_shader, GL_VERTEX_SHADER);
	const auto program	= glCreateProgram();

	glAttachShader(program, frag);
	glAttachShader(program, vert);

	glLinkProgram(program);

	glDetachShader(program, frag);
	glDetachShader(program, vert);

	return program;
}
