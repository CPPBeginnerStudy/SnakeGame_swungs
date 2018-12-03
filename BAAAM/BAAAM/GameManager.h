#pragma once
class GameManager
{
public:
	static GameManager& GetInstance()
	{
		static GameManager instance;
		return instance;
	}
// �ۺ� �Լ�
public:
	void Run();		// ����
	void Shutdown();// ����

// �����̺� �Լ�
private:
	void Init();	// �ʱ�ȭ
	void Release();	// ����
	void MainLoop();// ���η���

// �̱��� ������ ����... �ʿ��� �༮... 
private:
	GameManager() {}
	~GameManager() {}

// �����̺� ����
private:
	bool m_IsOn;
};

