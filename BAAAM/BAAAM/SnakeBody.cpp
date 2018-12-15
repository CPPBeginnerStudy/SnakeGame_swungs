#include "pch.h"
#include "SnakeBody.h"
#include "Console.h"


SnakeBody::SnakeBody()
	:m_Speed(1.f)
{
	m_SpeedX = 0.f;
	m_SpeedY = 0.f;
}


SnakeBody::~SnakeBody()
{
}

void SnakeBody::Update()
{
	// �̵��ϴ� �������� �ڵ� �̵�
	// �ٿ������ ��� �����ص� �ڵ����� ���� ��ȯ�������� �ʴ´�
	Move(m_IsRight ? Direction::RIGHT : Direction::LEFT, m_SpeedX);
	Move(m_IsBottom ? Direction::DOWN : Direction::UP, m_SpeedY);
}

void SnakeBody::Render()
{
	Object::Render();
}

void SnakeBody::OnKeyPress(BYTE _key)
{
	switch (_key)
	{
	case VK_UP:
	{
		m_IsBottom = false;
		m_SpeedX = 0.f;
		m_SpeedY = m_Speed;
	}
	break;
	case VK_DOWN:
	{
		m_IsBottom = true;
		m_SpeedX = 0.f;
		m_SpeedY = m_Speed;
	}
	break;
	case VK_LEFT:
	{
		m_IsRight = false;
		m_SpeedX = m_Speed;
		m_SpeedY = 0.f;
	}
	break;
	case VK_RIGHT:
	{
		m_IsRight = true;
		m_SpeedX = m_Speed;
		m_SpeedY = 0.f;

	}
	break;
	case 'Z':
	{
		// �̼� ���̱�
		m_Speed = std::max<float>(m_Speed - 0.1f, 0.1f);
	}
	break;
	case 'X':
	{
		// �̼� �ø���
		m_Speed = std::min<float>(m_Speed + 0.1f, 3.f);
	}
	break;
	}
}

