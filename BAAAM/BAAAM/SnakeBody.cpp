#include "pch.h"
#include "SnakeBody.h"
#include "Console.h"


SnakeBody::SnakeBody()
	:m_Speed(1.f)
	, m_Direction(Direction::RIGHT)
{
}


SnakeBody::~SnakeBody()
{
	// ���࿡ ������ ������ �Բ� �Ҵ����� ���ش�.  
	for (auto& pTail : m_TailList)
	{
		delete pTail;
	}

}

void SnakeBody::Update()
{
	 // �ϴ� �ӽ÷� 10% Ȯ���� ���� �߰�  
	 if (rand() % 100 < 10)
	 {
		AddTail();
	 }

	 // �����̱� ���� ���� ���� ��ġ�� �����س��´�.  
	 // ���� ������ �� ������ ��ġ�� �̵��Ѵ�.  
	 float prevX = m_X;
	 float prevY = m_Y;

	 // �̵��ϴ� �������� �ڵ� �̵�
	 // �ٿ������ ��� �����ص� �ڵ����� ���� ��ȯ�������� �ʴ´�
	 Move(m_Direction, m_Speed);
	
	 // �� ������ ���� ������ ��ġ�� ���õȴ�. (��, ���󰡴� ���°� �ȴ�.)  
	 for (auto& pTail : m_TailList)
	 {
		 float tempX = pTail->GetX();
		 float tempY = pTail->GetY();
		 pTail->SetX(prevX);
		 pTail->SetY(prevY);
		 prevX = tempX;
		 prevY = tempY;
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
		m_Speed = std::max<float>(m_Speed - 0.1f, 0.1f);
	}
	break;
	case 'X':
	{
		// �̼� �ø���
		m_Speed = std::min<float>(m_Speed + 0.1f, 3.f);
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

