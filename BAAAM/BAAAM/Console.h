#pragma once
class Console
{

public:
	// 싱글톤 패턴을 위해... 필요한 녀석...

	// 싱글톤 패턴은 프로그램 주기동안 단 하나의 인스턴스만 생성해 사용하는 패턴이다.
	// 최초 한 번만 메모리 할당하기 위해 앞에 static을 붙여서 정적 변수로 선언한다.
	// 정적 변수라고 부르는 건 할당해놓는 메모리 공간이 바뀌지 않아서인 거 같다
	// 전역 인스턴스이기 때문에 다른 객체에서 사용하기 쉽고 한번만 만들기 때문에 메모리 낭비를 방지하는 장점이 있다고 한다
	// 받아오고 싶으면 범위 지정 연산자 ::를 사용해서 Console::GetInstance() 처럼 쓴다
	// Console 인스턴스를 선언했으면 Console.Run(); 이런식으로 인스턴스에 점을 찍어서 함수를 사용하는 거 같고
	// 선언하지 않은 상태로도 함수를 쓸 때는 ::을 사용하는 듯하다.

	// 포인터와 주소값 반환, 레퍼런스

	// int* pa;
	// int 타입 변수의 주소값을 담을 수 있는 포인터 pa 선언
	// *pa 포인터 pa를 역참조, 즉 pa의 주소값이 실제로 담고 있는 값을 반환
	
	// int a;
	// &a a라는 변수의 주소값을 반환
	// int &a 

	// int& a = b;
	// 이미 이름이 붙어있는 변수에 또 다른 이름을 붙여주는 것
	// &a 와 b는 완전히 동일
	// 위의 주소값 반환과는 다른 의미이다
	// 포인터를 역참조하는 것과 비슷하다고 한다
	// 참조형은 매개 변수의 값을 수정하려는 경우나 매개 변수의 비싼 복사본을 만들지 않으려는 경우 함수 매개변수로 자주 사용된다.

	// 콘솔 인스턴스를 참조형(별명?)으로 반환한다. 
	// 굳이 콘솔 인스턴스 복사형을 만들 필요 없고 매개 변수를 직접 변화시켜야 하므로.
	// Console& A = instance; 
	// 레퍼런스 개념 이해하기 쥰내 어렵다
	static Console& GetInstance()
	{
		static Console instance;
		return instance;
	}

private:
	// 헤더에는 선언만 해준다
	Console();
	~Console();

public:
	void Init();
	void Release();

	void Clear();
	void SwapBuffer();

	void Print(char _shape, short _x, short _y);
	void PrintText(const std::string& _text, short _x, short _y);

	RECT     GetBoundaryBox() const;

private:
	short m_ScreenWidth;
	short m_ScreenHeight;

	// m_ScreenBuffer라는 이름의 short 타입 2개 사이즈 배열을 만든다
	// HANDLE 타입은 포인터의 다른 이름이라고 생각해도 된다고 한다

	// 더블버퍼링 
	// 스크린버퍼 2개를 만들고 백버퍼에 객체가 다 그려지면(렌더링되면) 
	// 현재 화면에 표시된 버퍼와 백버퍼를 서로 스왑하여 화면에 한번에 표시되도록 한다
	HANDLE m_ScreenBuffer[2];

	// 백버퍼 구분을 위한 인덱스
	short m_BackBufferIdx;

};

