#include "pch.h"
#include "SnakeBody.h"
#include "Console.h"


SnakeBody::SnakeBody()
	:m_Speed(1.f)
	, m_Direction(Direction::RIGHT)
{
}


SnakeBody::~SnakeBody()
{
}

void SnakeBody::Update()
{
	// 이동하던 방향으로 자동 이동
	// 바운더리에 닿아 실패해도 자동으로 방향 전환시켜주지 않는다
	Move(m_Direction, m_Speed);
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
		m_Direction = Direction::UP;
	}
	break;
	case VK_DOWN:
	{
		m_Direction = Direction::DOWN;
	}
	break;
	case VK_LEFT:
	{
		m_Direction = Direction::LEFT;
	}
	break;
	case VK_RIGHT:
	{
		m_Direction = Direction::RIGHT;
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
    /// > 현재 이속 조절했을 때 바로 적용되지 않고, 방향키를 이후 눌러줘야 적용되고 있습니다.
    /// > 왜 그런지 원인을 파악해보고, 방향키 누르지 않고도 Z, X로 이속조절시 바로 적용되게 수정해보면 좋을 듯 합니다..!
}

