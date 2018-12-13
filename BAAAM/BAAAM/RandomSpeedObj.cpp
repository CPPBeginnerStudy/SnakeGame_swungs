#include "pch.h"
#include "RandomSpeedObj.h"
#include "Console.h"


RandomSpeedObj::RandomSpeedObj()
{
}


RandomSpeedObj::~RandomSpeedObj()
{
}

void RandomSpeedObj::Update()
{
	// ȭ���� �ٿ������ ����� �ϸ� �ݴ� �������� ��ȯ�Ͽ� ��� �����̵��� �ϴ� �ڵ� 
	RECT boundaryBox = Console::GetInstance().GetBoundaryBox();

	// �ӷ� ���� �ּ� �ִ밪(�ӽ�)
	int speedMax = 3;
	int speedMin = 1;

	if (m_IsRight)
	{
		m_X += m_SpeedX;
		/// > m_X = m_X + m_Speed; �� ���� � ������ �ڽ��� ���� ���� �����Ǵ� ���
		/// > m_X += m_Speed; ó�� �ڽ��� ���� �ٸ� � ���� ���ϴ� ������ε� �� �� �ֽ��ϴ�.
		if (m_X > boundaryBox.right)
		{
			m_X = boundaryBox.right;
			m_IsRight = false;
			m_SpeedX = rand() % (speedMax - speedMin + 1) + speedMin;
		}
	}
	else
	{
		m_X -= m_SpeedX;
		if (m_X < boundaryBox.left)
		{
			m_X = boundaryBox.left;
			m_IsRight = true;
			m_SpeedX = rand() % (speedMax - speedMin + 1) + speedMin;
		}
	}

	if (m_IsBottom)
	{
		m_Y += m_SpeedY;
		if (m_Y > boundaryBox.bottom)
		{
			m_Y = boundaryBox.bottom;
			m_IsBottom = false;
			m_SpeedY = rand() % (speedMax - speedMin + 1) + speedMin;
		}
	}
	else
	{
		m_Y -= m_SpeedY;
		if (m_Y < boundaryBox.top)
		{
			m_Y = boundaryBox.top;
			m_IsBottom = true;
			m_SpeedY = rand() % (speedMax - speedMin + 1) + speedMin;
		}
	}

}

void RandomSpeedObj::Render()
{
	// �������̵��� �Լ��� �⺻������ �θ��Լ��� ȣ������ �ʴ´�. 
	// ���� �θ��Լ��� ȣ���� �ʿ䰡 ���� ��� �Ʒ��� ���� �θ�Ŭ����::�Լ��� ���� ȣ�����ش�. 
	// �θ� Ŭ������ ������ �ٸ��� ó���� �� ���ٸ�, �׳� �θ𲨸� ���⼭ �ٽ� ȣ�����ָ� �ȴ�. 
	Object::Render();
}
