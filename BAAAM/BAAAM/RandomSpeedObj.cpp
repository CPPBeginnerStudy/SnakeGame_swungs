#include "pch.h"
#include "RandomSpeedObj.h"
#include "Console.h"


RandomSpeedObj::RandomSpeedObj()
	: m_SpeedX(1)
	, m_SpeedY(1)
	, m_IsRight(true)
	, m_IsBottom(true)
{
	m_Shape = L'★';
}


RandomSpeedObj::~RandomSpeedObj()
{
}

void RandomSpeedObj::Update(float _dt)
{

	// 속력 랜덤 최소 최대값 /2될 값
	int speedMax = 6;
	int speedMin = 1;

	if (!Move(m_IsRight ? Direction::RIGHT : Direction::LEFT, m_SpeedX))
	{
		m_IsRight = !m_IsRight;
		m_SpeedX = rand() % (speedMax - speedMin + 1) + speedMin;
	}
	if (!Move(m_IsBottom ? Direction::DOWN : Direction::UP, m_SpeedY))
	{
		m_IsBottom = !m_IsBottom;
		m_SpeedY = rand() % (speedMax - speedMin + 1) + speedMin; 
	}
}

void RandomSpeedObj::Render()
{
	// 오버라이딩한 함수는 기본적으로 부모함수를 호출하지 않는다. 
	// 따라서 부모함수도 호출할 필요가 있을 경우 아래와 같이 부모클래스::함수명 으로 호출해준다. 
	// 부모 클래스의 구현과 다르게 처리할 게 없다면, 그냥 부모꺼를 여기서 다시 호출해주면 된다. 
	Object::Render();
}
