#pragma once
class GameManager
{
public:
	static GameManager& GetInstance()
	{
		static GameManager instance;
		return instance;
	}
// 퍼블릭 함수
public:
	void Run();		// 실행
	void Shutdown();// 종료

// 프라이빗 함수
private:
	void Init();	// 초기화
	void Release();	// 정리
	void MainLoop();// 메인루프

// 싱글톤 패턴을 위해... 필요한 녀석... 
private:
	GameManager() {}
	~GameManager() {}

// 프라이빗 변수
private:
	bool m_IsOn;
};

