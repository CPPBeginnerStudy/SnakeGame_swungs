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

	// ������ ��ǥ�ϱ� �ּҰ��� 1�ε� �̰ͺ��� �� �ӵ��� ���̰� ������ ��� ����?
	/// > ���� �����Դϴ�! �ӵ��� ������ ���ϱ��� ��Ʈ���ϰ� �ʹٸ�,
	/// > ���������� �Ǽ���(float)��ǥ�踦 ������ �ϰ�, �̸� �������Ҷ���
	/// > ���������� ��ȯ�ؼ� ���߾� �׸��� �����մϴ�.
{
}


Object::~Object()
{
}

void Object::Update()
{
	if (!Move(m_IsRight ? Direction::RIGHT : Direction::LEFT, m_SpeedX))
	{  
	    // �̵��� �����ϸ�(�ٿ������ �ɸ���) �ݴ� �������� ��ȯ  
	    // �Ʒ��� �ڵ�� bool�� ������ �ڽ��� ���� ������Ű�� �ڵ��̴�. (true->false, false->true)  
	    m_IsRight = !m_IsRight;  
	}  
	if (!Move(m_IsBottom ? Direction::DOWN : Direction::UP, m_SpeedY))
	{  
	    m_IsBottom = !m_IsBottom;  
	}  
}

void Object::Render()
{
	Console::GetInstance().Print(m_Shape, (short)m_X, (short)m_Y);
}

bool Object::Move(Direction _dir, float _distance)
{
	RECT boundaryBox = Console::GetInstance().GetBoundaryBox();
	switch (_dir)
	{
	case Direction::UP:
	{
		// ���� y��ǥ�� ���� ��輱���� ũ��(�Ʒ����̸�) �������� �̵��� �����ϴ�.
		if (m_Y > boundaryBox.top)
		{
			// ��û�� �Ÿ���ŭ �̵��� �õ��ϸ�, �ٿ������ �Ѿ�� �ʵ��� ó���Ѵ�.
			// std::max�� �ΰ��� ������ �� ū���� ��ȯ�ϴ� �Լ��̴�.
			// ��, m_Y - _distance �� �ٿ�������� ������, �ٿ�������� ��ȯ�Ͽ� �� ���ϰ��� ������ �ʰ��Ѵ�.
			m_Y = std::max<float>(m_Y - _distance, boundaryBox.top);

			// ���⿡ �Դٴ°� ����Ƶ� ������� �̵��� �Ѵٴ� ���̴�.
			return true;
		}
	}
	break;
	case Direction::DOWN:
	{
		// ���� y��ǥ�� �Ʒ��� ��輱���� ������(�����̸�) �Ʒ������� �̵��� �����ϴ�.
		if (m_Y < boundaryBox.bottom)
		{
			m_Y = std::min<float>(m_Y + _distance, boundaryBox.bottom);
			return true;
		}
	}
	break;
	case Direction::LEFT:
	{
		// ���� x��ǥ�� ���� ��輱���� ũ��(�������̸�) �������� �̵��� �����ϴ�.
		if (m_X > boundaryBox.left)
		{
			// �Ÿ��� 2�� ���ϴ� ������ x��ǥ�� y��ǥ�� �����̱� ����.
			m_X = std::max<float>(m_X - _distance * 2, boundaryBox.left);
			return true;
		}
	}
	break;
	case Direction::RIGHT:
	{
		// ���� x��ǥ�� ������ ��輱���� ������(�����̸�) ���������� �̵��� �����ϴ�.
		if (m_X < boundaryBox.right)
		{
			m_X = std::min<float>(m_X + _distance * 2, boundaryBox.right);
			return true;
		}
	}
	break;
	}
	// ���⿡ �Դٴ°� �ƹ� �̵��� ���� �ʾҴٴ� ���̴�.
	return false;
}

