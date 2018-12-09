#pragma once
class Object; // ���� ����
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

	void Update(); // ������Ʈ
	void Render(); // ������


// �����̺� ����
private:

	// ��� ������ ���������� m_ �� �ٿ��� ǥ���Ѵ�
	bool m_IsOn;
	std::list<Object*> m_ObjectList;

};

