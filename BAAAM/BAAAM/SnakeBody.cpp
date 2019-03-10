#include "pch.h"
#include "SnakeBody.h"
#include "Console.h"
#include "GameManager.h"


SnakeBody::SnakeBody()
	:m_Speed(1) // 1�� ������Ʈ �� �� �̵��� �Ÿ�
	, m_Direction(Direction::RIGHT)
{
	m_Shape = L'��';
}


SnakeBody::~SnakeBody()
{
	// ���࿡ ������ ������ �Բ� �Ҵ����� ���ش�.  
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

	 // �����̱� ���� ���� ���� ��ġ�� �����س��´�.  
	 // ���� ������ �� ������ ��ġ�� �̵��Ѵ�.  
	 int prevX = m_X;
	 int prevY = m_Y;

	 // �̵��ϴ� �������� �ڵ� �̵�
	 // �ٿ������ ��� �����ص� �ڵ����� ���� ��ȯ�������� �ʴ´�
	 Move(m_Direction, m_Speed);
	
	 // �� ������ ���� ������ ��ġ�� ���õȴ�. (��, ���󰡴� ���°� �ȴ�.)  
	 for (auto& pTail : m_TailList)
	 {
		 int tempX = pTail->GetX();
		 int tempY = pTail->GetY();
		 pTail->SetX(prevX);
		 pTail->SetY(prevY);
		 prevX = tempX;
		 prevY = tempY;
	 }

	 // �Ӹ��� ������ ��Ҵ��� üũ
	 for (auto& pTail : m_TailList)
	 {
		 // �� ������Ʈ x,y ��ǥ�� ������
		 if (m_X == pTail->GetX() &&
			 m_Y == pTail->GetY())
		 {
			 // ���� ����
			 GameManager::GetInstance().Shutdown();
			 return;
		 }
	 }

}

void SnakeBody::Render()
{
	Object::Render();
	// ������ ���� �����鵵 ������  
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
		// �̼� ���̱�
		// ��� ���ϴϱ� �ּ� ó��
		//m_Speed = std::max<float>(m_Speed - 0.1f, 0.1f);
	}
	break;
	case 'X':
	{
		// �̼� �ø���
		// ��� ���ϴϱ� �ּ� ó��
		//m_Speed = std::min<float>(m_Speed + 0.1f, 3.f);
	}
	break;
	}
    /// > ���� �̼� �������� �� �ٷ� ������� �ʰ�, ����Ű�� ���� ������� ����ǰ� �ֽ��ϴ�.
    /// > �� �׷��� ������ �ľ��غ���, ����Ű ������ �ʰ� Z, X�� �̼������� �ٷ� ����ǰ� �����غ��� ���� �� �մϴ�..!
}

void SnakeBody::AddTail()
{
	Object * pTail = new Object();
	pTail->SetShape(L'��');
	m_TailList.push_back(pTail);

}

