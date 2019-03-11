#include "pch.h"
#include "Object.h"
#include "Console.h"

Object::Object()
	:m_Shape(L' ')
	,m_Color(Color::WHITE)
	,m_Bgcolor(Color::BLACK)
	,m_X(0)
	,m_Y(0)


	// ������ ��ǥ�ϱ� �ּҰ��� 1�ε� �̰ͺ��� �� �ӵ��� ���̰� ������ ��� ����?
	/// > ���� �����Դϴ�! �ӵ��� ������ ���ϱ��� ��Ʈ���ϰ� �ʹٸ�,
	/// > ���������� �Ǽ���(float)��ǥ�踦 ������ �ϰ�, �̸� �������Ҷ���
	/// > ���������� ��ȯ�ؼ� ���߾� �׸��� �����մϴ�.
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
	// �Ÿ��� 2�� ���ϴ� ������ x��ǥ�� y��ǥ�� �����̱� ����.
	Console::GetInstance().Print(m_Shape, m_Color, m_Bgcolor, (short)(m_X * 2), (short)m_Y);
}

bool Object::Move(Direction _dir, int _distance)
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
			m_Y = std::max<int>(m_Y - _distance, boundaryBox.top);

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
			m_Y = std::min<int>(m_Y + _distance, boundaryBox.bottom);
			return true;
		}
	}
	break;
	case Direction::LEFT:
	{
		// ���� x��ǥ�� ���� ��輱���� ũ��(�������̸�) �������� �̵��� �����ϴ�.
		if (m_X > boundaryBox.left)
		{
			m_X = std::max<int>(m_X - _distance, boundaryBox.left);
			return true;
		}
	}
	break;
	case Direction::RIGHT:
	{
		// ���� x��ǥ�� ������ ��輱���� ������(�����̸�) ���������� �̵��� �����ϴ�.
		if (m_X < boundaryBox.right)
		{
			m_X = std::min<int>(m_X + _distance, boundaryBox.right);
			return true;
		}
	}
	break;
	}
	// ���⿡ �Դٴ°� �ƹ� �̵��� ���� �ʾҴٴ� ���̴�.
	return false;
}

