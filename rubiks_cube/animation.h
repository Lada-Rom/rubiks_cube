#pragma once
#ifndef __ANIMATION__H__

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class animation // �������� ��������
{
	static constexpr float speed = 1.0f; // ����� ��������
	glm::quat m_start;  // ��������� ��������
	glm::quat m_curr;   // ��������������� ��������
	glm::quat m_end;    // �������� ��������
	float timer = 0;    // ������
	bool finish = true; // �������� ���������

public:

	// ������ �������� (��������������� �����������)
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

	// ������ ��������
	void setup(const glm::quat& start, const glm::quat& end)
	{
		setup_ident(glm::normalize(start), glm::normalize(end));
	}

	// ������������
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

