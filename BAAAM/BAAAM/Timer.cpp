#include "pch.h"
#include "Timer.h"


Timer::Timer()
{
	// ������ �� �ʱ�ȭ
	Init();
}

Timer::~Timer()
{
}

void Timer::Init()
{
	// m_PrevTick ȣ������ ���� ���� �ð����� �ʱ�ȭ
	m_PrevTick = std::chrono::system_clock::now();
	m_Delay = 0.f;
	m_AccumDT = 0.f;
}

// ���� ƽ�� ���� ƽ ������ �ð���(�ʴ���)�� ����Ͽ� ��ȯ�ϴ� �Լ�
float Timer::GetDeltaTime()
{
	TickTime curTick = std::chrono::system_clock::now();
	Seconds deltaTime = curTick - m_PrevTick;
	// ����ƽ���� ����ƽ�� ������Ʈ���ֱ�
	m_PrevTick = curTick;

	// duratation Ÿ���� ��ǻ�� ������ �ð��̶� ��ȯ�� �ʿ�
	// count�Լ� - ��ǻ�� ������ �ð��� �츮�� ���ϴ� ������ �ð����� ȯ������(�� ��쿡�� �ʴ���)
	return deltaTime.count();
}

void Timer::SetDelay(float _delay)
{
	m_Delay = _delay;
	m_AccumDT = 0.f;
}

bool Timer::CheckDelay(float _dt)
{
	m_AccumDT += _dt;
	// ���� ��Ÿ Ÿ���� ���õ� ������ ������ ������
	if (m_AccumDT < m_Delay)
	{
		return false;
	}
	// ���ų� ũ�� true, �ֱⰡ �� �� ���ƿԴ�
	m_AccumDT = 0.f;
	return true;
}
