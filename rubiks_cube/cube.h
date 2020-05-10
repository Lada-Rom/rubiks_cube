#pragma once
#ifndef ____CUBE2_H_______

#define GLEW_STATIC
#include <vector>
#include <glew/glew.h>
#include <glfw/glfw3.h>
#include "transform.h"

struct vertex {
    glm::vec3 pos;
    glm::vec3 col;
};

class Cubes {
public:

    // инициализация
    void init() {
        /**********************
         *     7--------6
         *    /|       /|
         *   / |      / |
         *  3--------2  |
         *  |  |     |  |
         *  |  4-----|--5
         *  | /      | /
         *  |/       |/
         *  0--------1
         **********************/

    // вершины модели
    vertex data[] {
        //  позиция              |       цвет
        // 0, 1, 2
        {{-1.0f, -1.0f, 1.0f},      {1.0f, 0.0f, 0.0f}},
        {{1.0f, -1.0f, 1.0f},       {1.0f, 0.0f, 0.0f}},
        {{1.0f, 1.0f, 1.0f},        {1.0f, 0.0f, 0.0f}},
        // 0, 2, 3
        {{-1.0f, -1.0f, 1.0f},      {1.0f, 0.0f, 0.0f}},
        {{1.0f, 1.0f, 1.0f},        {1.0f, 0.0f, 0.0f}},
        {{-1.0f, 1.0f, 1.0f},       {1.0f, 0.0f, 0.0f}},
        // 1, 5, 6
        {{1.0f, -1.0f, 1.0f},       {1.0f, 1.0f, 0.0f}},
        {{1.0f, -1.0f, -1.0f},      {1.0f, 1.0f, 0.0f}},
        {{1.0f, 1.0f, -1.0f},       {1.0f, 1.0f, 0.0f}},
        // 1, 6, 2
        {{1.0f, -1.0f, 1.0f},       {1.0f, 1.0f, 0.0f}},
        {{1.0f, 1.0f, -1.0f},       {1.0f, 1.0f, 0.0f}},
        {{1.0f, 1.0f, 1.0f},        {1.0f, 1.0f, 0.0f}},
        // 5, 4, 7
        {{1.0f, -1.0f, -1.0f},      {0.0f, 1.0f, 0.0f}},
        {{-1.0f, -1.0f, -1.0f},     {0.0f, 1.0f, 0.0f}},
        {{-1.0f, 1.0f, -1.0f},      {0.0f, 1.0f, 0.0f}},
        // 5, 7, 6
        {{1.0f, -1.0f, -1.0f},      {0.0f, 1.0f, 0.0f}},
        {{-1.0f, 1.0f, -1.0f},      {0.0f, 1.0f, 0.0f}},
        {{1.0f, 1.0f, -1.0f},       {0.0f, 1.0f, 0.0f}},
        // 4, 0, 3
        {{-1.0f, -1.0f, -1.0f},     {0.0f, 1.0f, 1.0f}},
        {{-1.0f, -1.0f, 1.0f},      {0.0f, 1.0f, 1.0f}},
        {{-1.0f, 1.0f, 1.0f},       {0.0f, 1.0f, 1.0f}},
        // 4, 3, 7
        {{-1.0f, -1.0f, -1.0f},     {0.0f, 1.0f, 1.0f}},
        {{-1.0f, 1.0f, 1.0f},       {0.0f, 1.0f, 1.0f}},
        {{-1.0f, 1.0f, -1.0f},      {0.0f, 1.0f, 1.0f}},
        // 3, 2, 6
        {{-1.0f, 1.0f, 1.0f},       {0.0f, 0.0f, 1.0f}},
        {{1.0f, 1.0f, 1.0f},        {0.0f, 0.0f, 1.0f}},
        {{1.0f, 1.0f, -1.0f},       {0.0f, 0.0f, 1.0f}},
        // 3, 6, 7
        {{-1.0f, 1.0f, 1.0f},       {0.0f, 0.0f, 1.0f}},
        {{1.0f, 1.0f, -1.0f},       {0.0f, 0.0f, 1.0f}},
        {{-1.0f, 1.0f, -1.0f},      {0.0f, 0.0f, 1.0f}},
        // 4, 5, 1
        {{-1.0f, -1.0f, -1.0f},     {1.0f, 0.0f, 1.0f}},
        {{1.0f, -1.0f, -1.0f},      {1.0f, 0.0f, 1.0f}},
        {{1.0f, -1.0f, 1.0f},       {1.0f, 0.0f, 1.0f}},
        // 4, 1, 0
        {{-1.0f, -1.0f, -1.0f},     {1.0f, 0.0f, 1.0f}},
        {{1.0f, -1.0f, 1.0f},       {1.0f, 0.0f, 1.0f}},
        {{-1.0f, -1.0f, 1.0f},      {1.0f, 0.0f, 1.0f}},
    };

        // создаём буферы
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &inst_data);

        // инициализируем буфер вершин
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, pos));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, col));

        // для instance drawing
        glVertexAttribDivisor(0, 0);
        glVertexAttribDivisor(1, 0);
        
        // инициализируем буфер матриц для инстансов
        auto matrices = get_inst_data();
        constexpr size_t sz = sizeof(glm::mat4);
        constexpr size_t st = sizeof(glm::vec4);

        glBindBuffer(GL_ARRAY_BUFFER, inst_data);
        glBufferData(GL_ARRAY_BUFFER, sz * matrices.size(), matrices.data(), GL_STREAM_DRAW);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sz, (GLvoid*)0);
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sz, (GLvoid*)st);
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sz, (GLvoid*)(2 * st));
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sz, (GLvoid*)(3 * st));

        // для instanced drawing
        glVertexAttribDivisor(2, 1);
        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    
    ~Cubes() {
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &inst_data);
        glDeleteVertexArrays(1, &vao);
    }

    void draw(GLuint shader, const glm::mat4& proj, const glm::mat4& view) {
        // обновляем матрицы, если нужно
        update_data();
        glm::mat4 vp = proj * view;    // ViewProjection матрица

        glUseProgram(shader);

        auto u_vp = glGetUniformLocation(shader, "u_vp");
        glUniformMatrix4fv(u_vp, 1, GL_FALSE, glm::value_ptr(vp));

        // рисуем инстансы
        glBindVertexArray(vao);
        glDrawArraysInstanced(GL_TRIANGLES, 0, 36, (GLsizei)m_data.size());
        glBindVertexArray(0);
    }

    // поворот пояса
    void rotate_belt(int belt, int angle, int axis) {
        // belt - 0..2
        // 0 - ближний (проекция плоскости на ось вращения положительная)
        // 1 - средний
        // 2 - дальний

        // angle - -1 или 1 (влево, вправо)

        // axix - 0..2
        // 0 - ось x
        // 1 - ось y
        // 2 - ось z
        if (need_update) return;
        static const glm::vec3 ax[3]{
            {1, 0, 0},
            {0, 1, 0},
            {0, 0, 1}
        };

        constexpr float eps = 0.1f;
        const float coord = -(belt - 1) * offset;
        const float an = glm::radians(angle * 90.0f);

        // если кубик в плоскости пояса
        for (auto&& tr : m_data) {
            if (std::abs(tr.get_transform()[3][axis] - coord) < eps) {
                tr.rotate(an, ax[axis]);
            }
        }

        need_update = true;
    }

    // обновляем анимацию
    void update(float dt) {
        for (auto&& tr : m_data) {
            if (tr.update(dt) && !need_update)
                need_update = true;
        }
    }

private:

    static constexpr float offset = 2.1f; // смещение кубиков в пространстве

    // начальная расстановка кубиков
    std::vector<transform> generate() {
        std::vector<transform> result;
        for (int x{ -1 }; x < 2; ++x) {
            for (int y{ -1 }; y < 2; ++y) {
                for (int z{ -1 }; z < 2; ++z) {
                    if (x == 0 && y == 0 && z == 0) continue;
                    result.push_back({});
                    result.back().set_pos({ x * offset, y * offset, z * offset });
                }
            }
        }
        return result;
    }

    // копируем матрицы трансформаций, для последующей загрузки в буфер
    std::vector<glm::mat4> get_inst_data() {
        std::vector<glm::mat4> result;
        result.reserve(m_data.size());
        for (auto&& tr : m_data)
            result.push_back(tr.get_transform());
        return result;
    }

    void update_data() {
        // если нужно, обновляем буфер матриц для инстансов
        if (need_update) {
            auto matrices = get_inst_data();
            constexpr size_t sz = sizeof(glm::mat4);

            glBindBuffer(GL_ARRAY_BUFFER, inst_data);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sz * matrices.size(), matrices.data());
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            need_update = false;
        }
    }

    // флаг обновления буфера матриц для инстансов
    bool need_update = false;

    // вектор объектов кубиков(анимированных трансформаций)
    std::vector<transform> m_data = generate();

    GLuint vbo; // буфер вершин
    GLuint vao; // массив атрибутов
    GLuint inst_data;   // буфер матриц
};

#endif // !____CUBE2_H_______
