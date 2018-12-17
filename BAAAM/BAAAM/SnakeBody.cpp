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
	// �̵��ϴ� �������� �ڵ� �̵�
	// �ٿ������ ��� �����ص� �ڵ����� ���� ��ȯ�������� �ʴ´�
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
    /// > ���� �̼� �������� �� �ٷ� ������� �ʰ�, ����Ű�� ���� ������� ����ǰ� �ֽ��ϴ�.
    /// > �� �׷��� ������ �ľ��غ���, ����Ű ������ �ʰ� Z, X�� �̼������� �ٷ� ����ǰ� �����غ��� ���� �� �մϴ�..!
}

