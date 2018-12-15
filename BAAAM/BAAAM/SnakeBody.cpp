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
	RECT boundaryBox = Console::GetInstance().GetBoundaryBox();
	switch (_key)
	{
	case VK_UP:
	{
		m_Y -= 1 * m_Speed;
		if (m_Y < boundaryBox.top)
		{
			m_Y = boundaryBox.top;
		}
	}
	break;
	case VK_DOWN:
	{
		m_Y += 1 * m_Speed;
		if (m_Y > boundaryBox.bottom)
		{
			m_Y = boundaryBox.bottom;
		}
	}
	break;
	case VK_LEFT:
	{
		// x��ǥ�� y��ǥ�� ���� �����̱� ������ ������ ������ �����̷���
		// y��ǥ���� 2�辿 �������� �Ѵ�.
		m_X -= 2 * m_Speed;
		if (m_X < boundaryBox.left)
		{
			m_X = boundaryBox.left;
		}
	}
	break;
	case VK_RIGHT:
	{
		m_X += 2 * m_Speed;
		if (m_X > boundaryBox.right)
		{
			m_X = boundaryBox.right;
		}
	}
	break;
	case 'Z':
	{
		// �̼� ���̱�
		m_Speed -= 0.1f;
		if (m_Speed < 0.1f)
		{
			m_Speed = 0.1f;
		}
	}
	break;
	case 'X':
	{
		// �̼� �ø���
		m_Speed += 0.1f;
		if (m_Speed > 3.f)
		{
			m_Speed = 3.f;
		}
	}
	break;
	}
}

