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

    // �������������
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

    // ������� ������
    vertex data[] {
        //  �������              |       ����
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

        // ������ ������
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &inst_data);

        // �������������� ����� ������
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, pos));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, col));

        // ��� instance drawing
        glVertexAttribDivisor(0, 0);
        glVertexAttribDivisor(1, 0);
        
        // �������������� ����� ������ ��� ���������
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

        // ��� instanced drawing
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
        // ��������� �������, ���� �����
        update_data();
        glm::mat4 vp = proj * view;    // ViewProjection �������

        glUseProgram(shader);

        auto u_vp = glGetUniformLocation(shader, "u_vp");
        glUniformMatrix4fv(u_vp, 1, GL_FALSE, glm::value_ptr(vp));

        // ������ ��������
        glBindVertexArray(vao);
        glDrawArraysInstanced(GL_TRIANGLES, 0, 36, (GLsizei)m_data.size());
        glBindVertexArray(0);
    }

    // ������� �����
    void rotate_belt(int belt, int angle, int axis) {
        // belt - 0..2
        // 0 - ������� (�������� ��������� �� ��� �������� �������������)
        // 1 - �������
        // 2 - �������

        // angle - -1 ��� 1 (�����, ������)

        // axix - 0..2
        // 0 - ��� x
        // 1 - ��� y
        // 2 - ��� z
        if (need_update) return;
        static const glm::vec3 ax[3]{
            {1, 0, 0},
            {0, 1, 0},
            {0, 0, 1}
        };

        constexpr float eps = 0.1f;
        const float coord = -(belt - 1) * offset;
        const float an = glm::radians(angle * 90.0f);

        // ���� ����� � ��������� �����
        for (auto&& tr : m_data) {
            if (std::abs(tr.get_transform()[3][axis] - coord) < eps) {
                tr.rotate(an, ax[axis]);
            }
        }

        need_update = true;
    }

    // ��������� ��������
    void update(float dt) {
        for (auto&& tr : m_data) {
            if (tr.update(dt) && !need_update)
                need_update = true;
        }
    }

private:

    static constexpr float offset = 2.1f; // �������� ������� � ������������

    // ��������� ����������� �������
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

    // �������� ������� �������������, ��� ����������� �������� � �����
    std::vector<glm::mat4> get_inst_data() {
        std::vector<glm::mat4> result;
        result.reserve(m_data.size());
        for (auto&& tr : m_data)
            result.push_back(tr.get_transform());
        return result;
    }

    void update_data() {
        // ���� �����, ��������� ����� ������ ��� ���������
        if (need_update) {
            auto matrices = get_inst_data();
            constexpr size_t sz = sizeof(glm::mat4);

            glBindBuffer(GL_ARRAY_BUFFER, inst_data);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sz * matrices.size(), matrices.data());
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            need_update = false;
        }
    }

    // ���� ���������� ������ ������ ��� ���������
    bool need_update = false;

    // ������ �������� �������(������������� �������������)
    std::vector<transform> m_data = generate();

    GLuint vbo; // ����� ������
    GLuint vao; // ������ ���������
    GLuint inst_data;   // ����� ������
};

#endif // !____CUBE2_H_______
