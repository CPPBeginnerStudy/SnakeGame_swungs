#include "pch.h"
#include "GameManager.h"
#include "Console.h"
#include "Object.h"
#include "RandomSpeedObj.h"
#include "SnakeBody.h"

GameManager::GameManager()
	:m_IsOn(false)
	,m_pSnakeBody(nullptr)
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

	// 2개는 등속 기본 오브젝트
	for (int i = 0; i < 2; ++i)
	{
		Object* pObject = new Object();
		pObject->SetShape(L'O');
		pObject->SetX(rand() % boundaryBox.right);
		pObject->SetY(rand() % boundaryBox.bottom);
		m_ObjectList.push_back(pObject);
		//이 경우 초기화한대로 무조건 오른쪽 아래로 움직이게 되는데
		//인스턴스 생성 시 방향도 무작위로 지정하고 싶다
        /// > 방향을 결정하는 변수들의 setter함수를 추가해서 여기서 랜덤하게 셋팅하면 될듯해요.
		//노트북에서도 특문 잘나오네요..? 노트북에서는 깨져야 하는거 아닌가@_@
        /// > 원래 기본 빌드옵션이 유니코드이고, 저희가 유니코드용 타입으로 일괄변경했기 때문에(char -> wchar_t)
        /// > 특수문자들이 잘 나오는 것이 정상입니다.
        /// > 이전에 'O' 문자가 '뷁' 등으로 깨져서 보였던 이유는
        /// > 빌드옵션이 유니코드여서 WriteConsole()함수가 wchar_t 타입을 받아야하는데, char 타입으로 넘겨줬었기 때문입니다.
        /// > 빌드옵션에 상관없이 char문자를 출력하려면 WriteConsoleA()함수를 호출해야 합니다.
	}

	// 3개는 랜덤 속도 오브젝트(기본 오브젝트 상속)
	for (int i = 0; i < 3; ++i)
	{
		Object* pObject = new RandomSpeedObj();
		pObject->SetShape(L'♬');
		pObject->SetX(rand() % boundaryBox.right);
		pObject->SetY(rand() % boundaryBox.bottom);
		m_ObjectList.push_back(pObject);
	}

	// 우리가 직접 조종할 뱀의 몸통을 생성한다.  
	m_pSnakeBody = new SnakeBody();
	m_pSnakeBody->SetShape(L'▣');
	m_pSnakeBody->SetX(boundaryBox.right / 2);  // 중앙에 생성  
	m_pSnakeBody->SetY(boundaryBox.bottom / 2); // 중앙에 생성
	m_ObjectList.push_back(m_pSnakeBody);


	// 게임 시작시
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
	//키입력에 대한 처리
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
	// GetAsyncKeyState()함수는 현재 키보드의 특정 키의 눌린 상태를 반환한다.
	// 어떤 키를 확인할지는 인자로 받으며, VK_ 로 시작하는 매크로값으로 정해져있다.
	// 키값 종류 참고: https://docs.microsoft.com/ko-kr/windows/desktop/inputdev/virtual-key-codes
	// 반환값은 키의 눌린 상태에 대한 플래그값이며, short타입(2byte)에서 왼쪽끝과 오른쪽끝 비트를 비트플래그로 사용한다.
	// 현재 키가 눌려있는지를 왼쪽끝 비트로 알려주고, 이전에 눌린적 있었는지를 오른쪽끝 비트로 알려준다.
	// 즉, 총 4가지의 케이스가 존재한다.
	// 1. 0000 0000 0000 0000 = 0x0000 : 이전에 누른 적이 없고 호출 시점에서 안눌린 상태
	// 2. 1000 0000 0000 0000 = 0x8000 : 이전에 누른 적이 없고 호출 시점에서 눌린 상태
	// 3. 0000 0000 0000 0001 = 0x0001 : 이전에 누른 적이 있고 호출 시점에서 안눌린 상태
	// 4. 1000 0000 0000 0001 = 0x8001 : 이전에 누른 적이 있고 호출 시점에서 눌린 상태
	// 이를 통해 키가 현시점에서 처음 눌렸는지, 아니면 누르고 있는 상태였는지 등을 체크할 수 있지만,
	// 사실 일반적으로 이러한 구분까지는 필요없고, 키가 지금 눌려있는지 여부만 알면 되기 때문에
	// 아래와 같이 0x8000 플래그가 있는지를 비트연산하여 키의 눌림여부를 확인한다. (즉, 위의 2, 4번 케이스를 모두 true처리)

	// 아래 사용된 것은 비트 연산 중 and 연산
	// AND 연산은 두 값의 각 자릿수를 비교해, 두 값 모두에 1이 있을 때에만 1을, 나머지 경우에는 0을 계산한다. 
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		// ESC 키가 눌리면 프로그램 종료
		Shutdown();
	}

	// 방향키 입력 처리 (else if가 아닌 이유는, 여러 키가 같이 눌렸을때에 모두 처리해줘야하기 때문)
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		// 각 키입력에 대한 처리는 각 클래스의 핸들러에서 구현하도록 넘겨준다.
		// 그래야 메인로직이 깔끔해지고, 이후 작업하기 편해진다.

		// 그렇군.. 이건 처음부터 이렇게 짜긴 어렵겠다. 
		m_pSnakeBody->OnKeyPress(VK_UP);

		// 나중에 SnakeBody말고도 키입력을 받을 대상이 생기면 여기에 추가
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

	// 영문자키는 해당 문자 캐릭터(char)의 바이트값과 대응된다.
	if (GetAsyncKeyState('Z') & 0x8000)
	{
		m_pSnakeBody->OnKeyPress('Z');
	}
	if (GetAsyncKeyState('X') & 0x8000)
	{
		m_pSnakeBody->OnKeyPress('X');
	}
}



