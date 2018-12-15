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

	// �ӷ� ���� �ּ� �ִ밪 /2�� ��
	int speedMax = 6;
	int speedMin = 1;

	if (!Move(m_IsRight ? Direction::RIGHT : Direction::LEFT, m_SpeedX))
	{
		m_IsRight = !m_IsRight;
		m_SpeedX = (rand() % (speedMax - speedMin + 1) + speedMin) * 0.5f;
	}
	if (!Move(m_IsBottom ? Direction::DOWN : Direction::UP, m_SpeedY))
	{
		m_IsBottom = !m_IsBottom;
		m_SpeedY = (rand() % (speedMax - speedMin + 1) + speedMin) * 0.5f;
	}
}

void RandomSpeedObj::Render()
{
	// �������̵��� �Լ��� �⺻������ �θ��Լ��� ȣ������ �ʴ´�. 
	// ���� �θ��Լ��� ȣ���� �ʿ䰡 ���� ��� �Ʒ��� ���� �θ�Ŭ����::�Լ��� ���� ȣ�����ش�. 
	// �θ� Ŭ������ ������ �ٸ��� ó���� �� ���ٸ�, �׳� �θ𲨸� ���⼭ �ٽ� ȣ�����ָ� �ȴ�. 
	Object::Render();
}
