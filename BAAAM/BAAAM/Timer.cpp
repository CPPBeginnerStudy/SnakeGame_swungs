#include "pch.h"
#include "Timer.h"


Timer::Timer()
{
	// 생성할 때 초기화
	Init();
}

Timer::~Timer()
{
}

void Timer::Init()
{
	// m_PrevTick 호출했을 때의 현재 시각으로 초기화
	m_PrevTick = std::chrono::system_clock::now();
}

// 이전 틱과 현재 틱 사이의 시간차(초단위)를 계산하여 반환하는 함수
float Timer::GetDeltaTime()
{
	TickTime curTick = std::chrono::system_clock::now();
	Seconds deltaTime = curTick - m_PrevTick;
	// 현재틱으로 이전틱을 업데이트해주기
	m_PrevTick = curTick;

	// duratation 타입은 컴퓨터 단위의 시간이라 변환이 필요
	// count함수 - 컴퓨터 단위의 시간을 우리가 원하는 단위의 시간으로 환산해줌(이 경우에는 초단위)
	return deltaTime.count();
}
