#pragma once
#ifndef ___SHADER_H___

#define GLEW_STATIC
#include <glew/glew.h>
#include <glfw/glfw3.h>

#define STRINGIFY(text) #text

// вершинный шейдер
const GLchar* vertex_shader_str = STRINGIFY
(
    #version 330 core\n

    layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 col;
layout(location = 2) in mat4 model;

uniform mat4 u_vp;

out vec3 color;

void main() {
    gl_Position = u_vp * model * vec4(pos, 1.0f);
    color = col;
}
);

// фрагментный шейдер
const GLchar* fragment_shader_str = STRINGIFY
(
    #version 330 core\n

    in vec3 color;

out vec4 frag_color;

void main() {
    frag_color = vec4(color, 1.0f);
}
);

static GLuint create_program(const char* vx_shader, const char* fr_shader) {
    // компил€ци€ шейдера
    GLuint vx = glCreateShader(GL_VERTEX_SHADER);
    GLuint fr = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vx, 1, &vx_shader, nullptr);
    glCompileShader(vx);

    glShaderSource(fr, 1, &fr_shader, nullptr);
    glCompileShader(fr);

    GLuint program = glCreateProgram();
    glAttachShader(program, vx);
    glAttachShader(program, fr);
    glLinkProgram(program);

    glDeleteShader(vx);
    glDeleteShader(fr);

    return program;
}

#endif // !___SHADER_H___
