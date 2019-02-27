#pragma once
class Timer
{
	//기존 타입에 이름 맘대로 지어서 쓰기. 앞으로 ㅇㅇ로 부를 거라는 약속

	//특정 시점을 나타내는 타입
	using TickTime = std::chrono::system_clock::time_point;
	// 단위를 나타냄. 디폴트는 초. 실수형으로 나타내기 때문에 float을 넣음.
	using Seconds = std::chrono::duration<float>;

public:
	Timer();
	~Timer();

	void Init();
	float GetDeltaTime();

private:
	TickTime m_PrevTick;
};

