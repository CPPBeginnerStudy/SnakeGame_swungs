#include "pch.h"
#include "SnakeBody.h"
#include "Console.h"


SnakeBody::SnakeBody()
	:m_Speed(1.f)
{
}


SnakeBody::~SnakeBody()
{
}

void SnakeBody::Update()
{
	// �ƹ��͵� ���� �ʴ´�
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
		Move(Direction::UP, m_Speed);
	}
	break;
	case VK_DOWN:
	{
		Move(Direction::DOWN, m_Speed);
	}
	break;
	case VK_LEFT:
	{
		Move(Direction::LEFT, m_Speed);
	}
	break;
	case VK_RIGHT:
	{
		Move(Direction::RIGHT, m_Speed);
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

