#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <windows.h>

#include "snake.hpp"
#include "shaders.hpp"
#include "snake_renderer.hpp"

constexpr unsigned field_width	= 22;
constexpr unsigned field_height = 22;

static std::unique_ptr<snake>			snake_instance;
static std::unique_ptr<snake_renderer>	renderer;

static void key_callback(GLFWwindow* window, int key, int, int action, int)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_W:
			snake_instance->change_velocity(vec2{0, -1});
			break;

		case GLFW_KEY_S:
			snake_instance->change_velocity(vec2{0, 1});
			break;

		case GLFW_KEY_A:
			snake_instance->change_velocity(vec2{-1, 0});
			break;

		case GLFW_KEY_D:
			snake_instance->change_velocity(vec2{1, 0});
			break;

		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, true);
			break;
		}
	}
}

static std::pair<GLFWwindow*, GLuint> initialize()
{
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, false);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 16);

	const auto primary_monitor	= glfwGetPrimaryMonitor();
	const auto video_mode		= glfwGetVideoMode(primary_monitor);

	const auto window = glfwCreateWindow(video_mode->width, video_mode->height, 
		"Snake", primary_monitor, nullptr);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);

	glewExperimental = true;
	glewInit();

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	const auto program = shaders::link_program("fragment_shader.glsl", "vertex_shader.glsl");
	glUseProgram(program);

	snake_instance = std::make_unique<snake>(field_width, field_height);
	renderer = std::make_unique<snake_renderer>(snake_instance.get(), program, 
		video_mode->width, video_mode->height);

	return {window, program};
}

int __stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	const auto [window, program] = initialize();

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		static auto last_time	= glfwGetTime();
		const auto  time		= glfwGetTime();
		const auto  delta		= time - last_time;

		if (delta > 0.1)
		{
			snake_instance->update();
			last_time = time;

			char buffer[128];
			sprintf_s(buffer, "Snake ( %d )", snake_instance->get_score());
			glfwSetWindowTitle(window, buffer);
		}

		renderer->render();
		glfwSwapBuffers(window);
	}

	glUseProgram(0);
	glDeleteProgram(program);

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}