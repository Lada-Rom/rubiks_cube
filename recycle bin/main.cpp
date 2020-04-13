#define GLEW_STATIC
#if defined(_MSC_VER)
// Make MS math.h define M_PI
#define _USE_MATH_DEFINES
#endif
#include "cube.h"
#include "smallcube.h"

#include <glew/glew.h>
#include <glfw/glfw3.h>


#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <linmath.h>
#include <cstdio>
#include <iostream>
#include <cmath>

#define MAX_DELTA_T 0.01

// Animation speed (10.0 looks good)
#define ANIMATION_SPEED 10.0

GLfloat alpha = 180.f, beta = 180.f;
GLfloat zoom = 2.f;

Cube a;

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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action != GLFW_PRESS)
		return;

	switch (key) {
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(window, GLFW_TRUE);
		break;
	case GLFW_KEY_SPACE: {
		static bool done = false;
		if (!done && action == GLFW_PRESS) {
			done = true;
			a.Rotatebelt(1, 1); // одноразово делаешь что нужно
		}
		break;
	}
	case GLFW_KEY_LEFT:
		alpha += 5;
		break;
	case GLFW_KEY_RIGHT:
		alpha -= 5;
		break;
	case GLFW_KEY_UP:
		beta -= 5;
		break;
	case GLFW_KEY_DOWN:
		beta += 5;
		break;
	case GLFW_KEY_PAGE_UP:
		zoom -= 0.25f;
		if (zoom < 0.f)
			zoom = 0.f;
		break;
	case GLFW_KEY_PAGE_DOWN:
		zoom += 0.25f;
		break;
	default:
		break;
	}
}

//========================================================================
// Callback function for mouse button events
//========================================================================

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button != GLFW_MOUSE_BUTTON_LEFT)
		return;

	if (action == GLFW_PRESS) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwGetCursorPos(window, &cursorX, &cursorY);
	}
	else
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

//========================================================================
// Callback function for cursor motion events
//========================================================================

void cursor_position_callback(GLFWwindow* window, double x, double y) {
	if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
		alpha += (GLfloat)(x - cursorX) / 10.f;
		beta += (GLfloat)(y - cursorY) / 10.f;

		cursorX = x;
		cursorY = y;
	}
}

//========================================================================
// Callback function for scroll events
//========================================================================

void scroll_callback(GLFWwindow* window, double x, double y) {
	zoom += (float)y / 4.f;
	if (zoom < 0)
		zoom = 0;
}


//========================================================================
// Callback function for framebuffer resize events
//========================================================================

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	float ratio = 1.f;
	mat4x4 projection;

	if (height > 0)
		ratio = (float)width / (float)height;

	// Setup viewport
	glViewport(0, 0, width, height);

	// Change to the projection matrix and set our viewing volume
	glMatrixMode(GL_PROJECTION);
	mat4x4_perspective(projection,
		60.f * (float)M_PI / 180.f,
		ratio,
		1.f, 1024.f);
	glLoadMatrixf((const GLfloat*)projection);
}

void perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar) {
	const GLdouble pi = acos(-1);
	GLdouble fW, fH;

	//fH = tan( (fovY / 2) / 180 * pi ) * zNear;
	fH = tan(fovY / 360 * pi) * zNear;
	fW = fH * aspect;

	glFrustum(-fW, fW, -fH, fH, zNear, zFar);
}

GLFWwindow* initWindow(const int resX, const int resY) {
	glfwWindowHint(GLFW_SAMPLES, 4); // Оптимизационная штука
	GLFWwindow* window = glfwCreateWindow(800, 600, "CubeRube", nullptr, nullptr);

	glfwMakeContextCurrent(window);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Get info of GPU and supported OpenGL version
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("OpenGL version supported %s\n", glGetString(GL_VERSION));

	glEnable(GL_DEPTH_TEST); // Depth Testing
	glDepthFunc(GL_LEQUAL);
	glDisable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	return window;
}

void draw_scene(GLFWwindow* window) {
	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// We don't want to modify the projection matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Move back
	glTranslatef(0.0, 0.0, -zoom);
	// Rotate the view
	glRotatef(beta, 1.0, 0.0, 0.0);
	glRotatef(alpha, 0.0, 0.0, 1.0);
	glRotatef(0, 0.0, 1.0, 0.0);
}

int main(int argc, char** argv) {
	int width, height;
	if (!glfwInit()) { //Инициализация GLFW
		fprintf(stderr, "Failed to initialize GLFW\n");
		return NULL;
	}
	glewExperimental = GL_TRUE;
	if (!glewInit()) { //Инициализация GLFW
		fprintf(stderr, "Failed to initialize GLFW\n");
		return NULL;
	} //Иниализация GLEW для управления указателями GL
	glEnable(GL_DEPTH_TEST);

	GLFWwindow* window = initWindow(1024, 620);

	glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetScrollCallback(window, scroll_callback);

	//gladLoadGL(glfwGetProcAddress);
	glfwSwapInterval(1);

	glfwGetFramebufferSize(window, &width, &height);
	framebuffer_size_callback(window, width, height);

	SmallCube cube1;
	SmallCube cube2;

		while (!glfwWindowShouldClose(window)) {
			// Scale to window size
			GLint windowWidth, windowHeight;
			glfwGetWindowSize(window, &windowWidth, &windowHeight);
			glViewport(0, 0, windowWidth, windowHeight);

			// Draw stuff
			glClearColor(0.0, 0.8, 0.3, 1.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			draw_scene(window);
			a.updatebelt();
			a.Draw();

			// Update Screen
			glfwSwapBuffers(window);

			// Check for any input, or window movement
			glfwPollEvents();
		}

		glfwDestroyWindow(window);
		glfwTerminate(); //очистка ресурсов
}
