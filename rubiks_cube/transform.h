#pragma once
#ifndef ___TRANSFORM_H____
#include "animation.h"

// анимированная трансформация
class transform {

    glm::quat m_rot = glm::identity<glm::quat>();   // вращение
    glm::mat4 m_pos = glm::identity<glm::mat4>();   // положение в пространстве
    glm::mat4 m_transform = glm::identity<glm::mat4>(); // итоговая матрица

    bool need_update = false;   // флаг обновления
    animation m_anim;           // анимация вращения

public:

    // тик анимации
    bool update(float dt) {
        if (m_anim.is_done()) return false;
        m_rot = m_anim.interpolate(dt);
        need_update = true;
        return true;
    }

    // установка анимированного вращения
    void rotate(float angle, const glm::vec3& axis) {
        if (!m_anim.is_done()) return;
        m_anim.setup(m_rot, glm::rotate(m_rot, angle, glm::inverse(m_rot) * axis));
        need_update = true;
    }

    // установка положения
    void set_pos(const glm::vec3& pos) {
        m_pos = glm::translate(glm::identity<glm::mat4>(), pos);
        need_update = true;
    }

    // геттер матрицы модели
    const glm::mat4& get_transform() {
        if (need_update) {
            m_transform = glm::mat4(m_rot) * m_pos;
            need_update = false;
        }
        return m_transform;
    }
};

#endif // !___TRANSFORM_H____
