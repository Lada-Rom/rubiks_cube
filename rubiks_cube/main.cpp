#include "cube.h"
#include "shader.h"
#include <glew/glew.h>
#include <glfw/glfw3.h>
#include <iostream>

static GLFWwindow* window = nullptr;
static int width = 0;
static int height{ 0 };

glm::mat4 proj; // матрица перспективной проекции
glm::mat4 view; // матрица вида

bool ready{ false };

static Cubes obj;

static void key_cb(GLFWwindow*, int key, int, int action, int)
{
	if (action != GLFW_PRESS) return;
	static int belt = 0;
	switch (key)
	{
	case GLFW_KEY_Q:    // против часовой вокруг оси z
		obj.rotate_belt(belt, 1, 2);
		break;
	case GLFW_KEY_E:    // по часовой вокруг оси z
		obj.rotate_belt(belt, -1, 2);
		break;
	case GLFW_KEY_A:    // по часовой вокруг оси y
		obj.rotate_belt(belt, -1, 1);
		break;
	case GLFW_KEY_D:    // против часовой вокруг оси y
		obj.rotate_belt(belt, 1, 1);
		break;
	case GLFW_KEY_W:    // по часовой вокруг оси x
		obj.rotate_belt(belt, -1, 0);
		break;
	case GLFW_KEY_S:    // против часовой вокруг оси x
		obj.rotate_belt(belt, 1, 0);
		break;
	case GLFW_KEY_KP_1: // выбираем ближний пояс
		belt = 0;
		break;
	case GLFW_KEY_KP_2: // выбираем средний пояс
		belt = 1;
		break;
	case GLFW_KEY_KP_3: // выбираем дальний пояс
		belt = 2;
		break;
	}
}

bool init()
{
	if (ready) return ready;
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		glfwTerminate();
		return false;
	};
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(800, 600, "TestOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_cb);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwSwapInterval(1);
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 1000.0f);
	view = glm::lookAt(glm::vec3{ 10, 10, 20 }, glm::vec3{ 0,0,0 }, glm::vec3{ 0,1,0 });
	obj.init();

	return ready = true;
}

	int run()
	{
		if (!init()) return -1;

		glClearColor(0.2f, 0.5f, 0.8f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		auto shader = create_program(vertex_shader_str, fragment_shader_str);
		glfwSetTime(0);

		while (!glfwWindowShouldClose(window))
		{
			obj.update(float(glfwGetTime()));
			glfwSetTime(0);
			glfwPollEvents();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			obj.draw(shader, proj, view);
			glfwSwapBuffers(window);
		}

		glDeleteProgram(shader);
		return 0;
	}

	

int main()
{
		return run();;
}