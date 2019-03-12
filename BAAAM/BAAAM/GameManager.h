#pragma once
class Object; // 전방 선언
class SnakeBody;
class Apple;
class DeathZone;

class GameManager
{

public:
	// 싱글톤 패턴을 위해... 필요한 녀석... 
	static GameManager& GetInstance()
	{
		static GameManager instance;
		return instance;
	}

// 생성자 소멸자
private:
	GameManager();
	~GameManager();

// 퍼블릭 함수
public:
	void Run();		// 실행
	void Shutdown();// 종료

// 프라이빗 함수
private:
	void Init();	// 초기화
	void Release();	// 정리
	void MainLoop();// 메인루프

	void Update(float _dt); // 업데이트
	void Render(); // 렌더링

	void KeyInputHandling(float _dt);


// 프라이빗 변수
private:

	// 멤버 변수는 관습적으로 m_ 을 붙여서 표현한다
	bool m_IsOn;
	std::list<Object*> m_ObjectList;
	SnakeBody* m_pSnakeBody;
	Apple* m_pApple;
	DeathZone* m_pDeathZone;
	float m_GameSpeed;

};

