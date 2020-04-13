
#include "cube.h"
#include "shader.h"
#include <glfw/glfw3.h>
#include <iostream>
#include <cstdio>
#include <iostream>
#include <cmath>


int Random(int min, int max) {
	return min + rand() % (max - min);
}

GLFWwindow* window = nullptr;
int width = 0;
int height{ 0 };

glm::mat4x4 proj; // матрица перспективной проекции
glm::mat4x4 view; // матрица вида


Cubes obj;

#define MAX_DELTA_T 0.01

// Animation speed (10.0 looks good)
#define ANIMATION_SPEED 10.0

GLfloat alpha = 0.1f, beta = 0.1f;
GLfloat zoom = 2.f;

GLuint shader;

double cursorX;
double cursorY;

#define GRIDW 50
#define GRIDH 50
#define VERTEXNUM (GRIDW*GRIDH)

#define QUADW (GRIDW - 1)
#define QUADH (GRIDH - 1)
#define QUADNUM (QUADW*QUADH)

GLuint quad[4 * QUADNUM];
using namespace std;

double dt;
double p[GRIDW][GRIDH];
double vx[GRIDW][GRIDH], vy[GRIDW][GRIDH];
double ax[GRIDW][GRIDH], ay[GRIDW][GRIDH];

static void key_cb(GLFWwindow*, int key, int, int action, int)
{
	if (action != GLFW_PRESS) return;
	static int belt = 0;
	switch (key)
	{
	case GLFW_KEY_SPACE: {
		static bool done = false;
		if (!done && action == GLFW_PRESS) {
			
			done = true;
		}
		break;
	}
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
	case GLFW_KEY_RIGHT: // выбираем ближний пояс
		belt = 0;
		break;
	case GLFW_KEY_DOWN: // выбираем средний пояс
		belt = 1;
		break;
	case GLFW_KEY_LEFT: // выбираем дальний пояс
		belt = 2;
		break;
	}
}

bool leftbutton{ false };
bool rightbutton{ false };

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwGetCursorPos(window, &cursorX, &cursorY);
		leftbutton = true;
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwGetCursorPos(window, &cursorX, &cursorY);
		rightbutton = true;
	}
	else
	{ 
		leftbutton = false;
		rightbutton = false;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

void cursor_position_callback(GLFWwindow* window, double x, double y) {
	if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
		if(y < cursorY)
		{ 
			alpha = abs(alpha);
			alpha += (GLfloat)(x - cursorX) / 1000000000000000000000000.f;
		}
		else
		{
			alpha = -abs(alpha);
			alpha -= (GLfloat)(x - cursorX) / 1000000000000000000000000.f;
		}
		if (x < cursorX)
		{ 
			beta = abs(beta);
			beta += (GLfloat)(y - cursorY) / 1000000000000000000000000.f;
		}
		else
		{
			beta = -abs(beta);
			beta -= (GLfloat)(y - cursorY) / 1000000000000000000000000.f;
		}

		glUseProgram(shader);

		if(leftbutton == true)
		{ 
			view = glm::rotate(view, beta, glm::vec3(0.0, 1.0, 0.0));
		}
		if(rightbutton == true)
		{ 
			view = glm::rotate(view, alpha, glm::vec3(1.0, 0.0, 0.0));
		}

		auto u_vp = glGetUniformLocation(shader, "view");
		glUniformMatrix4fv(u_vp, 1, GL_FALSE, glm::value_ptr(view));

		cursorX = x;
		cursorY = y;
	}
}


void scroll_callback(GLFWwindow* window, double x, double y) {
	zoom += (float)y / 4.f;
	if (zoom < 0)
		zoom = 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	float ratio = 1.f;

	if (height > 0)
		ratio = (float)width / (float)height;

	// Setup viewport
	glViewport(0, 0, width, height);

	// Change to the projection matrix and set our viewing volume
	glUseProgram(shader);

	auto u_vp = glGetUniformLocation(shader, "proj");
	glUniformMatrix4fv(u_vp, 1, GL_FALSE, glm::value_ptr(proj));
}

bool init()
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		glfwTerminate();
		return false;
	};
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(800, 600, "Cuberube", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_cb);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetScrollCallback(window, scroll_callback);

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

	return true;
}


int run()
{
	if (!init()) return -1;

	glClearColor(0.2f, 0.5f, 0.8f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	shader = create_program(vertex_shader_str, fragment_shader_str);
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
	if (init())
	{
		run();
	}
	glfwTerminate();
}