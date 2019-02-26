#include "pch.h"
#include "Object.h"
#include "Console.h"

Object::Object()
	:m_Shape(L' ')
	,m_X(0.f)
	,m_Y(0.f)


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

}

void Object::Render()
{
	// �Ÿ��� 2�� ���ϴ� ������ x��ǥ�� y��ǥ�� �����̱� ����.
	Console::GetInstance().Print(m_Shape, (short)(m_X * 2), (short)m_Y);
}

bool Object::Move(Direction _dir, float _distance)
{
	RECT boundaryBox = Console::GetInstance().GetBoundaryBox();

	//cmd ��ǥ�� �ΰ��� ��ǥ�� ��ȯ
	float minX = (float)boundaryBox.left / 2;
	float maxX = (float)boundaryBox.right / 2;
	float minY = (float)boundaryBox.top;
	float maxY = (float)boundaryBox.bottom;

	switch (_dir)
	{
	case Direction::UP:
	{
		// ���� y��ǥ�� ���� ��輱���� ũ��(�Ʒ����̸�) �������� �̵��� �����ϴ�.
		if (m_Y > minY)
		{
			// ��û�� �Ÿ���ŭ �̵��� �õ��ϸ�, �ٿ������ �Ѿ�� �ʵ��� ó���Ѵ�.
			// std::max�� �ΰ��� ������ �� ū���� ��ȯ�ϴ� �Լ��̴�.
			// ��, m_Y - _distance �� �ٿ�������� ������, �ٿ�������� ��ȯ�Ͽ� �� ���ϰ��� ������ �ʰ��Ѵ�.
			m_Y = std::max<float>(m_Y - _distance, minY);

			// ���⿡ �Դٴ°� ����Ƶ� ������� �̵��� �Ѵٴ� ���̴�.
			return true;
		}
	}
	break;
	case Direction::DOWN:
	{
		// ���� y��ǥ�� �Ʒ��� ��輱���� ������(�����̸�) �Ʒ������� �̵��� �����ϴ�.
		if (m_Y < maxY)
		{
			m_Y = std::min<float>(m_Y + _distance, maxY);
			return true;
		}
	}
	break;
	case Direction::LEFT:
	{
		// ���� x��ǥ�� ���� ��輱���� ũ��(�������̸�) �������� �̵��� �����ϴ�.
		if (m_X > minX)
		{
			m_X = std::max<float>(m_X - _distance, minX);
			return true;
		}
	}
	break;
	case Direction::RIGHT:
	{
		// ���� x��ǥ�� ������ ��輱���� ������(�����̸�) ���������� �̵��� �����ϴ�.
		if (m_X < maxX)
		{
			m_X = std::min<float>(m_X + _distance, maxX);
			return true;
		}
	}
	break;
	}
	// ���⿡ �Դٴ°� �ƹ� �̵��� ���� �ʾҴٴ� ���̴�.
	return false;
}

