#include "pch.h"
#include "Apple.h"


Apple::Apple()
{
	m_Shape = L'£À';
	m_Color = Color::RED;
}

Apple::~Apple()
{
}

void Apple::Update(float _dt)
{
}

void Apple::Render()
{
	Object::Render();
}