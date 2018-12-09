#include "pch.h"
#include "GameManager.h"
#include "Console.h"
#include "Object.h"


GameManager::GameManager()
	:m_IsOn(false)
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
	for (int i = 0; i < 5; ++i)
	{
		Object* pObject = new Object();
		pObject->Init();
		pObject->SetShape('O');
		pObject->SetX(rand() % boundaryBox.right);
		pObject->SetY(rand() % boundaryBox.bottom);
		m_ObjectList.push_back(pObject);
	}

	// ���� ���۽�
	m_IsOn = true;
}

void GameManager::Release()
{
	Console::GetInstance().Release();

	for (auto& pObject : m_ObjectList)
	{
		pObject->Release();
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




