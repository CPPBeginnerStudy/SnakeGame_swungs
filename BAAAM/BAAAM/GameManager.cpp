#include "pch.h"
#include "GameManager.h"
#include "Console.h"
#include "Object.h"


GameManager::GameManager()
	:m_IsOn(false)
	//std::list<Object*> m_ObjectList; 이건 왜 초기화 안시켜줘요?
	//m_ObjectList.clear(); 안해도됨?
    /// > list와 같은 클래스타입은 여기서 직접 초기화를 하지 않아도
    /// > 기본생성자가 자동으로 호출되어 알아서 초기화됩니다.
    /// > 아직 내부에 아무런 자료도 보관하고 있지 않기 때문에 clear()함수도 호출할 필요가 없습니다.
    /// GameManager라는 클래스의 생성시 그 멤버변수인 m_IsOn과 m_ObjectList도 같이 생성되고,
    /// GameManager라는 클래스가 소멸시 그 멤버변수들도 같이 소멸됩니다.
    /// 즉 GameManager클래스가 생성되는 시점에 멤버변수인 m_ObjectList는 항상 비어있다는 것이지요. (새로 생기기 때문에)
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
    /// > 오오 이런 추가공부 좋네요!ㅎㅎ..(제가 다 설명드리지 못해 죄송합니다ㅠ)
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
        /// > 사실 cout은 함수가 아니라 변수인데 이것은 조금 고급기법이기 때문에
        /// > 더이상의 자세한 설명은 생략하겠습니다..^^;;
		//cout은 콘솔아웃. 콘솔 창에 출력 
		//std::cout << "Hello World!\n";

		// 질문. 
		// 다른 클래스에서 GameManager의 MainLoop 함수를 호출했는데 그 클래스에도
		// 우연히 Update라는 이름의 함수가 정의되어 있으면 어떤 함수가 불리게 되나요?
		// 변수도 동일한 경우에 어떻게되나요?
        /// > 이 함수 스코프 내에서 사용되는 함수, 변수는 기본적으로 이 함수가 속한 클래스의 것을 사용합니다.
        /// > 함수나 변수의 이름이 같은게 있다고 하더라도 결국은 다른 클래스의 것을 사용하려면
        /// > 그 클래스의 인스턴스.함수(); 또는 인스턴스.변수; 로 써야만 하기 때문에 충돌나지 않습니다.
        /// > 이 함수를 호출한 곳이 다른 클래스여도 마찬가지입니다.
        /// > 결국에는 이 함수 내부에서는 이 함수가 선언된 클래스의 영역입니다. (GameManager::)

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




