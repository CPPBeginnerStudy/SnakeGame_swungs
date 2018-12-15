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
	// 화면의 바운더리를 벗어나려 하면 반대 방향으로 전환하여 계속 움직이도록 하는 코드 
	RECT boundaryBox = Console::GetInstance().GetBoundaryBox();

	// 속력 랜덤 최소 최대값(임시) /2될 값
	int speedMax = 6;
	int speedMin = 1;

	if (m_IsRight)
	{
		m_X += 2 * m_SpeedX;
		/// > m_X = m_X + m_Speed; 와 같이 어떤 변수가 자신의 값을 토대로 수정되는 경우
		/// > m_X += m_Speed; 처럼 자신의 값에 다른 어떤 값을 더하는 방식으로도 쓸 수 있습니다.
		if (m_X > boundaryBox.right)
		{
			m_X = boundaryBox.right;
			m_IsRight = false;
			m_SpeedX = (rand() % (speedMax - speedMin + 1) + speedMin) * 0.5f;
		}
	}
	else
	{
		m_X -= 2 * m_SpeedX;
		if (m_X < boundaryBox.left)
		{
			m_X = boundaryBox.left;
			m_IsRight = true;
			m_SpeedX = (rand() % (speedMax - speedMin + 1) + speedMin) * 0.5f;
		}
	}

	if (m_IsBottom)
	{
		m_Y += 1 * m_SpeedY;
		if (m_Y > boundaryBox.bottom)
		{
			m_Y = boundaryBox.bottom;
			m_IsBottom = false;
			m_SpeedY = (rand() % (speedMax - speedMin + 1) + speedMin) * 0.5f;
		}
	}
	else
	{
		m_Y -= 1 * m_SpeedY;
		if (m_Y < boundaryBox.top)
		{
			m_Y = boundaryBox.top;
			m_IsBottom = true;
			m_SpeedY = (rand() % (speedMax - speedMin + 1) + speedMin) * 0.5f;
		}
	}

}

void RandomSpeedObj::Render()
{
	// 오버라이딩한 함수는 기본적으로 부모함수를 호출하지 않는다. 
	// 따라서 부모함수도 호출할 필요가 있을 경우 아래와 같이 부모클래스::함수명 으로 호출해준다. 
	// 부모 클래스의 구현과 다르게 처리할 게 없다면, 그냥 부모꺼를 여기서 다시 호출해주면 된다. 
	Object::Render();
}
