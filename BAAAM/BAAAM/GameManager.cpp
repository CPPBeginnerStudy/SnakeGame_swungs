#include "pch.h"
#include "GameManager.h"
#include "Console.h"
#include "Object.h"
#include "RandomSpeedObj.h"
#include "SnakeBody.h"

GameManager::GameManager()
	:m_IsOn(false)
	,m_pSnakeBody(nullptr)
	//std::list<Object*> m_ObjectList; �̰� �� �ʱ�ȭ �Ƚ������?
	//m_ObjectList.clear(); ���ص���?
    /// > list�� ���� Ŭ����Ÿ���� ���⼭ ���� �ʱ�ȭ�� ���� �ʾƵ�
    /// > �⺻�����ڰ� �ڵ����� ȣ��Ǿ� �˾Ƽ� �ʱ�ȭ�˴ϴ�.
    /// > ���� ���ο� �ƹ��� �ڷᵵ �����ϰ� ���� �ʱ� ������ clear()�Լ��� ȣ���� �ʿ䰡 �����ϴ�.
    /// GameManager��� Ŭ������ ������ �� ��������� m_IsOn�� m_ObjectList�� ���� �����ǰ�,
    /// GameManager��� Ŭ������ �Ҹ�� �� ��������鵵 ���� �Ҹ�˴ϴ�.
    /// �� GameManagerŬ������ �����Ǵ� ������ ��������� m_ObjectList�� �׻� ����ִٴ� ��������. (���� ����� ������)
{
}

GameManager::~GameManager()
{
}

//------------------�ۺ� �Լ�
void GameManager::Run()
{
	// ���� ����� 
	Init();
	MainLoop();
	Release();
}

void GameManager::Shutdown()
{
	// ���� �����
	m_IsOn = false;
}

//------------------�����̺� �Լ�

void GameManager::Init()
{
	//���� �õ� �ʱ�ȭ
	//srand �Լ��� ���� ���� �õ带 ���������� ������ 
	//rand() �Լ��� �׻� �Ȱ��� ������ ������ �ݺ������� �̾Ƴ���.
	//time �Լ��� 1970.1.1���� ��������� ���� �� ��ȯ�� ��
	//srand �Ű� ���� Ÿ�Կ� �´� unsigned int Ÿ������ ��ȯ�Ͽ� ����
    /// > ���� �̷� �߰����� ���׿�!����..(���� �� ����帮�� ���� �˼��մϴ٤�)
	srand((unsigned int)time(nullptr));

	auto& console = Console::GetInstance();
	console.Init();
	//Console::GetInstance().Init();

	RECT boundaryBox = console.GetBoundaryBox();

	// 2���� ��� �⺻ ������Ʈ
	for (int i = 0; i < 2; ++i)
	{
		Object* pObject = new Object();
		pObject->SetShape(L'O');
		pObject->SetX(rand() % boundaryBox.right);
		pObject->SetY(rand() % boundaryBox.bottom);
		m_ObjectList.push_back(pObject);
		//�� ��� �ʱ�ȭ�Ѵ�� ������ ������ �Ʒ��� �����̰� �Ǵµ�
		//�ν��Ͻ� ���� �� ���⵵ �������� �����ϰ� �ʹ�
        /// > ������ �����ϴ� �������� setter�Լ��� �߰��ؼ� ���⼭ �����ϰ� �����ϸ� �ɵ��ؿ�.
		//��Ʈ�Ͽ����� Ư�� �߳����׿�..? ��Ʈ�Ͽ����� ������ �ϴ°� �ƴѰ�@_@
        /// > ���� �⺻ ����ɼ��� �����ڵ��̰�, ���� �����ڵ�� Ÿ������ �ϰ������߱� ������(char -> wchar_t)
        /// > Ư�����ڵ��� �� ������ ���� �����Դϴ�.
        /// > ������ 'O' ���ڰ� '��' ������ ������ ������ ������
        /// > ����ɼ��� �����ڵ忩�� WriteConsole()�Լ��� wchar_t Ÿ���� �޾ƾ��ϴµ�, char Ÿ������ �Ѱ������ �����Դϴ�.
        /// > ����ɼǿ� ������� char���ڸ� ����Ϸ��� WriteConsoleA()�Լ��� ȣ���ؾ� �մϴ�.
	}

	// 3���� ���� �ӵ� ������Ʈ(�⺻ ������Ʈ ���)
	for (int i = 0; i < 3; ++i)
	{
		Object* pObject = new RandomSpeedObj();
		pObject->SetShape(L'��');
		pObject->SetX(rand() % boundaryBox.right);
		pObject->SetY(rand() % boundaryBox.bottom);
		m_ObjectList.push_back(pObject);
	}

	// �츮�� ���� ������ ���� ������ �����Ѵ�.  
	m_pSnakeBody = new SnakeBody();
	m_pSnakeBody->SetShape(L'��');
	m_pSnakeBody->SetX(boundaryBox.right / 2);  // �߾ӿ� ����  
	m_pSnakeBody->SetY(boundaryBox.bottom / 2); // �߾ӿ� ����
	m_ObjectList.push_back(m_pSnakeBody);


	// ���� ���۽�
	m_IsOn = true;
}

void GameManager::Release()
{
	Console::GetInstance().Release();

	for (auto& pObject : m_ObjectList)
	{
		delete pObject;
	}

	m_ObjectList.clear();
}

void GameManager::MainLoop()
{
	while (m_IsOn)
	{	
		//std��� ���� �����̽��ȿ� ����Ǿ� �ִ� cout�Լ��� ����Ѵٴ� ��.
        /// > ��� cout�� �Լ��� �ƴ϶� �����ε� �̰��� ���� ��ޱ���̱� ������
        /// > ���̻��� �ڼ��� ������ �����ϰڽ��ϴ�..^^;;
		//cout�� �ܼ־ƿ�. �ܼ� â�� ��� 
		//std::cout << "Hello World!\n";

		// ����. 
		// �ٸ� Ŭ�������� GameManager�� MainLoop �Լ��� ȣ���ߴµ� �� Ŭ��������
		// �쿬�� Update��� �̸��� �Լ��� ���ǵǾ� ������ � �Լ��� �Ҹ��� �ǳ���?
		// ������ ������ ��쿡 ��Եǳ���?
        /// > �� �Լ� ������ ������ ���Ǵ� �Լ�, ������ �⺻������ �� �Լ��� ���� Ŭ������ ���� ����մϴ�.
        /// > �Լ��� ������ �̸��� ������ �ִٰ� �ϴ��� �ᱹ�� �ٸ� Ŭ������ ���� ����Ϸ���
        /// > �� Ŭ������ �ν��Ͻ�.�Լ�(); �Ǵ� �ν��Ͻ�.����; �� ��߸� �ϱ� ������ �浹���� �ʽ��ϴ�.
        /// > �� �Լ��� ȣ���� ���� �ٸ� Ŭ�������� ���������Դϴ�.
        /// > �ᱹ���� �� �Լ� ���ο����� �� �Լ��� ����� Ŭ������ �����Դϴ�. (GameManager::)

		Update();
		Render();

		// 30ms ����
		Sleep(30);
	}
}

void GameManager::Update()
{
	//Ű�Է¿� ���� ó��
	KeyInputHandling();

	for (auto& pObject : m_ObjectList)
	{
		pObject->Update();
	}
}

void GameManager::Render()
{
	auto& console = Console::GetInstance();
	console.Clear();

	for (auto& pObject : m_ObjectList)
	{
		pObject->Render();
	}

	console.SwapBuffer();
}

void GameManager::KeyInputHandling()
{
	// GetAsyncKeyState()�Լ��� ���� Ű������ Ư�� Ű�� ���� ���¸� ��ȯ�Ѵ�.
	// � Ű�� Ȯ�������� ���ڷ� ������, VK_ �� �����ϴ� ��ũ�ΰ����� �������ִ�.
	// Ű�� ���� ����: https://docs.microsoft.com/ko-kr/windows/desktop/inputdev/virtual-key-codes
	// ��ȯ���� Ű�� ���� ���¿� ���� �÷��װ��̸�, shortŸ��(2byte)���� ���ʳ��� �����ʳ� ��Ʈ�� ��Ʈ�÷��׷� ����Ѵ�.
	// ���� Ű�� �����ִ����� ���ʳ� ��Ʈ�� �˷��ְ�, ������ ������ �־������� �����ʳ� ��Ʈ�� �˷��ش�.
	// ��, �� 4������ ���̽��� �����Ѵ�.
	// 1. 0000 0000 0000 0000 = 0x0000 : ������ ���� ���� ���� ȣ�� �������� �ȴ��� ����
	// 2. 1000 0000 0000 0000 = 0x8000 : ������ ���� ���� ���� ȣ�� �������� ���� ����
	// 3. 0000 0000 0000 0001 = 0x0001 : ������ ���� ���� �ְ� ȣ�� �������� �ȴ��� ����
	// 4. 1000 0000 0000 0001 = 0x8001 : ������ ���� ���� �ְ� ȣ�� �������� ���� ����
	// �̸� ���� Ű�� ���������� ó�� ���ȴ���, �ƴϸ� ������ �ִ� ���¿����� ���� üũ�� �� ������,
	// ��� �Ϲ������� �̷��� ���б����� �ʿ����, Ű�� ���� �����ִ��� ���θ� �˸� �Ǳ� ������
	// �Ʒ��� ���� 0x8000 �÷��װ� �ִ����� ��Ʈ�����Ͽ� Ű�� �������θ� Ȯ���Ѵ�. (��, ���� 2, 4�� ���̽��� ��� trueó��)

	// �Ʒ� ���� ���� ��Ʈ ���� �� and ����
	// AND ������ �� ���� �� �ڸ����� ����, �� �� ��ο� 1�� ���� ������ 1��, ������ ��쿡�� 0�� ����Ѵ�. 
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		// ESC Ű�� ������ ���α׷� ����
		Shutdown();
	}

	// ����Ű �Է� ó�� (else if�� �ƴ� ������, ���� Ű�� ���� ���������� ��� ó��������ϱ� ����)
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		// �� Ű�Է¿� ���� ó���� �� Ŭ������ �ڵ鷯���� �����ϵ��� �Ѱ��ش�.
		// �׷��� ���η����� ���������, ���� �۾��ϱ� ��������.

		// �׷���.. �̰� ó������ �̷��� ¥�� ��ưڴ�. 
		m_pSnakeBody->OnKeyPress(VK_UP);

		// ���߿� SnakeBody���� Ű�Է��� ���� ����� ����� ���⿡ �߰�
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_pSnakeBody->OnKeyPress(VK_DOWN);
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_pSnakeBody->OnKeyPress(VK_LEFT);
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_pSnakeBody->OnKeyPress(VK_RIGHT);
	}

	// ������Ű�� �ش� ���� ĳ����(char)�� ����Ʈ���� �����ȴ�.
	if (GetAsyncKeyState('Z') & 0x8000)
	{
		m_pSnakeBody->OnKeyPress('Z');
	}
	if (GetAsyncKeyState('X') & 0x8000)
	{
		m_pSnakeBody->OnKeyPress('X');
	}
}



