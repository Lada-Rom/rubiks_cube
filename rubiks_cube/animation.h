#pragma once
#ifndef __ANIMATION__H__

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class animation // анимация вращения
{
	static constexpr float speed = 1.0f; // время поворота
	glm::quat m_start;  // начальное вращение
	glm::quat m_curr;   // интерполируемое вращение
	glm::quat m_end;    // конечное вращение
	float timer = 0;    // таймер
	bool finish = true; // анимация закончена

public:

	// запуск анимации (нормализованные кватернионы)
	void setup_ident(const glm::quat& start, const glm::quat& end)
	{
		m_start = start;
		m_end = end;
		float a = glm::dot(m_start, m_end);
		if (a < 0)
			m_curr = -m_end;
		else
			m_curr = m_end;
		m_curr -= m_start;
		finish = false;
	}

	// запуск анимации
	void setup(const glm::quat& start, const glm::quat& end)
	{
		setup_ident(glm::normalize(start), glm::normalize(end));
	}

	// интерполяция
	glm::quat interpolate(float dt)
	{
		timer += dt;
		if (timer >= speed)
		{
			finish = true;
			timer = 0;
			return m_end;
		}
		return glm::normalize(m_start + m_curr * timer);
	}

	bool is_done() { return finish; }
};

#endif // __ANIMATION__H

