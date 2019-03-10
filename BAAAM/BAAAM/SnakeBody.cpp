#include "pch.h"
#include "SnakeBody.h"
#include "Console.h"
#include "GameManager.h"


SnakeBody::SnakeBody()
	:m_Speed(1) // 1번 업데이트 될 때 이동할 거리
	, m_Direction(Direction::RIGHT)
{
	m_Shape = L'▣';
}


SnakeBody::~SnakeBody()
{
	// 만약에 꼬리가 있으면 함께 할당해제 해준다.  
	for (auto& pTail : m_TailList)
	{
		delete pTail;
	}

}

//|a-b| <1
//	-1<a-b<1
//	-1<a-b => a>b-1
//	a-b<1 => a<b+1
	

void SnakeBody::Update(float _dt)
{

	 // 움직이기 전에 먼저 원래 위치를 보관해놓는다.  
	 // 다음 꼬리가 이 보관된 위치로 이동한다.  
	 int prevX = m_X;
	 int prevY = m_Y;

	 // 이동하던 방향으로 자동 이동
	 // 바운더리에 닿아 실패해도 자동으로 방향 전환시켜주지 않는다
	 Move(m_Direction, m_Speed);
	
	 // 각 꼬리는 이전 꼬리의 위치로 셋팅된다. (즉, 따라가는 형태가 된다.)  
	 for (auto& pTail : m_TailList)
	 {
		 int tempX = pTail->GetX();
		 int tempY = pTail->GetY();
		 pTail->SetX(prevX);
		 pTail->SetY(prevY);
		 prevX = tempX;
		 prevY = tempY;
	 }

	 // 머리가 꼬리에 닿았는지 체크
	 for (auto& pTail : m_TailList)
	 {
		 // 두 오브젝트 x,y 좌표가 같으면
		 if (m_X == pTail->GetX() &&
			 m_Y == pTail->GetY())
		 {
			 // 게임 종료
			 GameManager::GetInstance().Shutdown();
			 return;
		 }
	 }

}

void SnakeBody::Render()
{
	Object::Render();
	// 나에게 붙은 꼬리들도 렌더링  
	for (auto& pTail : m_TailList)
	{
		pTail->Render();
	}

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
		// 이속 줄이기
		// 사용 안하니까 주석 처리
		//m_Speed = std::max<float>(m_Speed - 0.1f, 0.1f);
	}
	break;
	case 'X':
	{
		// 이속 늘리기
		// 사용 안하니까 주석 처리
		//m_Speed = std::min<float>(m_Speed + 0.1f, 3.f);
	}
	break;
	}
    /// > 현재 이속 조절했을 때 바로 적용되지 않고, 방향키를 이후 눌러줘야 적용되고 있습니다.
    /// > 왜 그런지 원인을 파악해보고, 방향키 누르지 않고도 Z, X로 이속조절시 바로 적용되게 수정해보면 좋을 듯 합니다..!
}

void SnakeBody::AddTail()
{
	Object * pTail = new Object();
	pTail->SetShape(L'※');
	m_TailList.push_back(pTail);

}

