#include "pch.h"
#include "Object.h"
#include "Console.h"

Object::Object()
	:m_Shape(' ')
	,m_X(0)
	,m_Y(0)
	,m_Speed(0)
	,m_SpeedMin(1) 	// ������ ��ǥ�ϱ� �ּҰ��� 1�ε� �̰ͺ��� �� �ӵ��� ���̰� ������ ��� ����?
	,m_SpeedMax(5)
	,m_IsRight(true)
	,m_IsBottom(true)
{
}


Object::~Object()
{
}

void Object::Init()
{
}

void Object::Release()
{
}

void Object::Update()
{
	// ȭ���� �ٿ������ ����� �ϸ� �ݴ� �������� ��ȯ�Ͽ� ��� �����̵��� �ϴ� �ڵ� 
	RECT boundaryBox = Console::GetInstance().GetBoundaryBox();

	if (m_IsRight)
	{
		m_X = m_X + m_Speed;
		if (m_X > boundaryBox.right)
		{
			m_X = boundaryBox.right;
			m_IsRight = false;
			m_Speed = rand() % (m_SpeedMax - m_SpeedMin + 1) + m_SpeedMin;
		}
	}
	else
	{
		m_X = m_X - m_Speed;
		if (m_X < boundaryBox.left)
		{
			m_X = boundaryBox.left;
			m_IsRight = true;	
			m_Speed = rand() % (m_SpeedMax - m_SpeedMin + 1) + m_SpeedMin;
		}
	}

	if (m_IsBottom)
	{
		m_Y = m_Y + m_Speed;
		if (m_Y > boundaryBox.bottom)
		{
			m_Y = boundaryBox.bottom;
			m_IsBottom = false;
			m_Speed = rand() % (m_SpeedMax - m_SpeedMin + 1) + m_SpeedMin;
		}
	}
	else
	{
		m_Y = m_Y - m_Speed;
		if (m_Y < boundaryBox.top)
		{
			m_Y = boundaryBox.top;
			m_IsBottom = true;
			m_Speed = rand() % (m_SpeedMax - m_SpeedMin + 1) + m_SpeedMin;
		}
	}

	}
	


}

void Object::Render()
{
	Console::GetInstance().Print(m_Shape, m_X, m_Y);
}
