#pragma once
class Timer
{
	//���� Ÿ�Կ� �̸� ����� ��� ����. ������ ������ �θ� �Ŷ�� ���

	//Ư�� ������ ��Ÿ���� Ÿ��
	using TickTime = std::chrono::system_clock::time_point;
	// ������ ��Ÿ��. ����Ʈ�� ��. �Ǽ������� ��Ÿ���� ������ float�� ����.
	using Seconds = std::chrono::duration<float>;

public:
	Timer();
	~Timer();

	void Init();
	float GetDeltaTime();

private:
	TickTime m_PrevTick;
};

