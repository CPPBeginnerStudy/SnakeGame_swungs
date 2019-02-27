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
