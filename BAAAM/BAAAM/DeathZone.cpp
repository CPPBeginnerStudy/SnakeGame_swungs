#include "pch.h"
#include "Console.h"
#include "DeathZone.h"



DeathZone::DeathZone()
{
}


DeathZone::~DeathZone()
{
	DestroyLines();
}

void DeathZone::Update(float _dt)
{
}

void DeathZone::Render()
{
	for (auto& pObject : m_DeathLines)
	{
		pObject->Render();
	}
}

void DeathZone::GenerateLines()
{
	DestroyLines();

	RECT boundaryBox = Console::GetInstance().GetBoundaryBox();
	int x = boundaryBox.left;
	int y = boundaryBox.top;
	Direction dir = Direction::RIGHT;

	while (true)
	{
		switch (dir)
		{
		case Direction::UP: --y; break;
		case Direction::DOWN: ++y; break;
		case Direction::LEFT: --x; break;
		case Direction::RIGHT: ++x; break;
		}

		if(x > boundaryBox.right)
		{
			x = boundaryBox.right;
			dir = Direction::DOWN;
		}
		else if (y > boundaryBox.bottom)
		{
			y = boundaryBox.bottom;
			dir = Direction::LEFT;
		}
		else if (x < boundaryBox.left)
		{
			x = boundaryBox.left;
			dir = Direction::UP;
		}
		else if(y < boundaryBox.top)
		{
			break;
		}

		Object *pObject = new Object();
		pObject->SetX(x);
		pObject->SetY(y);
		pObject->SetShape(L'¢É');
		pObject->SetColor(Color::DARK_YELLOW);
		m_DeathLines.push_back(pObject);

	}
}

void DeathZone::DestroyLines()
{
	for (auto& pObject : m_DeathLines)
	{
		delete pObject;
	}
}

bool DeathZone::IsInDeathZone(Object * _pObject) const
{
	if (_pObject == nullptr)
	{
		return false;
	}

	for (auto& pObject : m_DeathLines)
	{
		if (pObject->GetX() == _pObject->GetX() &&
			pObject->GetY() == _pObject->GetY())
		{
			return true;
		}
	}

	return false;


}
