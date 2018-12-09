#include "pch.h"
#include "GameManager.h"
#include "Console.h"
#include "Object.h"


GameManager::GameManager()
	:m_IsOn(false)
	//std::list<Object*> m_ObjectList; 이건 왜 초기화 안시켜줘요?
	//m_ObjectList.clear(); 안해도됨?
{
}

GameManager::~GameManager()
{
}

//------------------퍼블릭 함수
void GameManager::Run()
{
	// 게임 실행시 
	Init();
	MainLoop();
	Release();
}

void GameManager::Shutdown()
{
	// 게임 종료시
	m_IsOn = false;
}

//------------------프라이빗 함수

void GameManager::Init()
{
	//랜덤 시드 초기화
	//srand 함수를 통해 랜덤 시드를 변경해주지 않으면 
	//rand() 함수는 항상 똑같은 패턴의 난수를 반복적으로 뽑아낸다.
	//time 함수로 1970.1.1부터 현재까지의 누적 초 반환한 후
	//srand 매개 변수 타입에 맞는 unsigned int 타입으로 변환하여 기입
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

	// 게임 시작시
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
		//std라는 네임 스페이스안에 선언되어 있는 cout함수를 사용한다는 뜻.
		//cout은 콘솔아웃. 콘솔 창에 출력 
		//std::cout << "Hello World!\n";

		// 질문. 
		// 다른 클래스에서 GameManager의 MainLoop 함수를 호출했는데 그 클래스에도
		// 우연히 Update라는 이름의 함수가 정의되어 있으면 어떤 함수가 불리게 되나요?
		// 변수도 동일한 경우에 어떻게되나요?

		Update();
		Render();

		// 30ms 정지
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




