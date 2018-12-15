#include "pch.h"
#include "Object.h"
#include "Console.h"

Object::Object()
	:m_Shape(' ')
	,m_X(0.f)
	,m_Y(0.f)
	,m_SpeedX(1.f)    
	,m_SpeedY(1.f)  
	,m_IsRight(true)   
	,m_IsBottom(true)  

	// 정수형 좌표니까 최소값은 1인데 이것보다 더 속도를 줄이고 싶으면 어떻게 하지?
	/// > 좋은 질문입니다! 속도를 정수값 이하까지 컨트롤하고 싶다면,
	/// > 내부적으로 실수형(float)좌표계를 가지게 하고, 이를 렌더링할때에
	/// > 정수형으로 변환해서 맞추어 그리면 가능합니다.
{
}


Object::~Object()
{
}

void Object::Update()
{
	// 화면의 바운더리를 벗어나려 하면 반대 방향으로 전환하여 계속 움직이도록 하는 코드 
	RECT boundaryBox = Console::GetInstance().GetBoundaryBox();

	// 속력 랜덤 최소 최대값(임시)
	int speedMax = 1;
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
			m_SpeedX = rand() % (speedMax - speedMin + 1) + speedMin;
		}
	}
	else
	{
		m_X -= 2 * m_SpeedX;
		if (m_X < boundaryBox.left)
		{
			m_X = boundaryBox.left;
			m_IsRight = true;	
			m_SpeedX = rand() % (speedMax - speedMin + 1) + speedMin;
		}
	}

	if (m_IsBottom)
	{
		m_Y += 1 * m_SpeedY;
		if (m_Y > boundaryBox.bottom)
		{
			m_Y = boundaryBox.bottom;
			m_IsBottom = false;
			m_SpeedY = rand() % (speedMax - speedMin + 1) + speedMin;
		}
	}
	else
	{
		m_Y -= 1 * m_SpeedY;
		if (m_Y < boundaryBox.top)
		{
			m_Y = boundaryBox.top;
			m_IsBottom = true;
			m_SpeedY = rand() % (speedMax - speedMin + 1) + speedMin;
		}
	}

	}
	
void Object::Render()
{
	Console::GetInstance().Print(m_Shape, (short)m_X, (short)m_Y);
}
