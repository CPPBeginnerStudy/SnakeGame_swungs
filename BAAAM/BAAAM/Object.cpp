#include "pch.h"
#include "Object.h"
#include "Console.h"

Object::Object()
	:m_Shape(L' ')
	,m_Color(Color::WHITE)
	,m_Bgcolor(Color::BLACK)
	,m_X(0)
	,m_Y(0)


	// 정수형 좌표니까 최소값은 1인데 이것보다 더 속도를 줄이고 싶으면 어떻게 하지?
	/// > 좋은 질문입니다! 속도를 정수값 이하까지 컨트롤하고 싶다면,
	/// > 내부적으로 실수형(float)좌표계를 가지게 하고, 이를 렌더링할때에
	/// > 정수형으로 변환해서 맞추어 그리면 가능합니다.
{
}


Object::~Object()
{
}

void Object::Update(float _dt)
{

}

void Object::Render()
{
	// 거리를 2배 곱하는 이유는 x좌표가 y좌표의 절반이기 때문.
	Console::GetInstance().Print(m_Shape, m_Color, m_Bgcolor, (short)(m_X * 2), (short)m_Y);
}

bool Object::Move(Direction _dir, int _distance)
{
	RECT boundaryBox = Console::GetInstance().GetBoundaryBox();

	switch (_dir)
	{
	case Direction::UP:
	{
		// 현재 y좌표가 위쪽 경계선보다 크면(아래쪽이면) 위쪽으로 이동이 가능하다.
		if (m_Y > boundaryBox.top)
		{
			// 요청된 거리만큼 이동을 시도하며, 바운더리를 넘어서지 않도록 처리한다.
			// std::max는 두개의 인자중 더 큰것을 반환하는 함수이다.
			// 즉, m_Y - _distance 가 바운더리보다 작으면, 바운더리값을 반환하여 그 이하값이 나오지 않게한다.
			m_Y = std::max<int>(m_Y - _distance, boundaryBox.top);

			// 여기에 왔다는건 어찌됐든 어느정도 이동은 한다는 뜻이다.
			return true;
		}
	}
	break;
	case Direction::DOWN:
	{
		// 현재 y좌표가 아래쪽 경계선보다 작으면(위쪽이면) 아래쪽으로 이동이 가능하다.
		if (m_Y < boundaryBox.bottom)
		{
			m_Y = std::min<int>(m_Y + _distance, boundaryBox.bottom);
			return true;
		}
	}
	break;
	case Direction::LEFT:
	{
		// 현재 x좌표가 왼쪽 경계선보다 크면(오른쪽이면) 왼쪽으로 이동이 가능하다.
		if (m_X > boundaryBox.left)
		{
			m_X = std::max<int>(m_X - _distance, boundaryBox.left);
			return true;
		}
	}
	break;
	case Direction::RIGHT:
	{
		// 현재 x좌표가 오른쪽 경계선보다 작으면(왼쪽이면) 오른쪽으로 이동이 가능하다.
		if (m_X < boundaryBox.right)
		{
			m_X = std::min<int>(m_X + _distance, boundaryBox.right);
			return true;
		}
	}
	break;
	}
	// 여기에 왔다는건 아무 이동도 하지 않았다는 뜻이다.
	return false;
}

