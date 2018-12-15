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
	// 아무것도 하지 않는다
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
		// 이속 줄이기
		m_Speed = std::max<float>(m_Speed - 0.1f, 0.1f);
	}
	break;
	case 'X':
	{
		// 이속 늘리기
		m_Speed = std::min<float>(m_Speed + 0.1f, 3.f);
	}
	break;
	}
}

