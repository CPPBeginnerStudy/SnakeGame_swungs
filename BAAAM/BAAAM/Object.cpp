#include "pch.h"
#include "Object.h"
#include "Console.h"

Object::Object()
	:m_Shape(' ')
	,m_X(0)
	,m_Y(0)
	,m_Speed(0)
	,m_SpeedMin(1)
	,m_SpeedMax(3)
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

	// �ӵ� ��ȭ �� ������ ����
	bool IsBoundary = false;

	// ������ ��ǥ�ϱ� �ּҰ��� 1�ε� �̰ͺ��� �� �ӵ��� ���̰� ������ ��� ����?

	if (m_IsRight)
	{
		m_X = m_X + m_Speed;
		if (m_X > boundaryBox.right)
		{
			m_X = boundaryBox.right;
			m_IsRight = false;
			IsBoundary = true;
		}
	}
	else
	{
		m_X = m_X - m_Speed;
		if (m_X < boundaryBox.left)
		{
			m_X = boundaryBox.left;
			m_IsRight = true;	
			IsBoundary = true;
		}
	}

	if (m_IsBottom)
	{
		m_Y = m_Y + m_Speed;
		if (m_Y > boundaryBox.bottom)
		{
			m_Y = boundaryBox.bottom;
			m_IsBottom = false;
			IsBoundary = true;
		}
	}
	else
	{
		m_Y = m_Y - m_Speed;
		if (m_Y < boundaryBox.top)
		{
			m_Y = boundaryBox.top;
			m_IsBottom = true;
			IsBoundary = true;
		}
	}

	// �𼭸����� ƨ������ �ӵ� �����ϰ� ��ȭ�����ش�
	if (IsBoundary)
	{
		// ���� �õ� �ʱ�ȭ. ���� �ؾ� �ǳ� �̰�
		srand((unsigned int)time(nullptr));
		m_Speed = rand() % (m_SpeedMax- m_SpeedMin +1) + m_SpeedMin;
	}
	


}

void Object::Render()
{
	Console::GetInstance().Print(m_Shape, m_X, m_Y);
}
