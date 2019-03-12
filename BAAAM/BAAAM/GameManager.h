#pragma once
class Object; // ���� ����
class SnakeBody;
class Apple;
class DeathZone;

class GameManager
{

public:
	// �̱��� ������ ����... �ʿ��� �༮... 
	static GameManager& GetInstance()
	{
		static GameManager instance;
		return instance;
	}

// ������ �Ҹ���
private:
	GameManager();
	~GameManager();

// �ۺ� �Լ�
public:
	void Run();		// ����
	void Shutdown();// ����

// �����̺� �Լ�
private:
	void Init();	// �ʱ�ȭ
	void Release();	// ����
	void MainLoop();// ���η���

	void Update(float _dt); // ������Ʈ
	void Render(); // ������

	void KeyInputHandling(float _dt);


// �����̺� ����
private:

	// ��� ������ ���������� m_ �� �ٿ��� ǥ���Ѵ�
	bool m_IsOn;
	std::list<Object*> m_ObjectList;
	SnakeBody* m_pSnakeBody;
	Apple* m_pApple;
	DeathZone* m_pDeathZone;
	float m_GameSpeed;

};

