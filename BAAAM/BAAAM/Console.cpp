#include "pch.h"
#include "Console.h"

// 생성자 - 콘솔 인스턴스를 생성할 때 자동으로 호출
// 인자가 있는 생성자도 정의할 수 있다고 한다
// 사실 안적어줘도 디폴트 생성자는 호출한다고 한다..
Console::Console()
	: m_ScreenWidth(0)
	, m_ScreenHeight(0)
	, m_BackBufferIdx(0)
{
	// 널포인터
	m_ScreenBuffer[0] = nullptr;
	m_ScreenBuffer[1] = nullptr;
}

// 소멸자 - 콘솔 인스턴스를 소멸할 때 자동으로 호출 
Console::~Console()
{
}

void Console::Init()
{
	// system - 매개 변수로 전달받은 커맨드를 실행하는 함수.
	// 흠... 커맨드는 없으니까 그냥 문자열 출력하고 끝나려나
    /// > system함수는 cmd창에서 직접 명령어 치는것과 동일하게 명령어를 실행시키는 함수입니다.
    /// > 아래의 mode가 콘솔 커맨드이며, 실제로 cmd창을 열어서 동일하게 치면 콘솔창 크기가 변경됩니다.
	system("mode con: lines=30 cols=90");

	//cmd창 크기 설정(30개행, 90개열)
	m_ScreenWidth = 90;
	m_ScreenHeight = 30;

	// 커서 깜빡임 제거를 위한 옵션
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = FALSE;

	// 스크린버퍼 2개 생성 후 초기화
	// 아래 내용은 이해 안해도 됨?
    /// > 후움...대강.. 각 함수들이 그 함수명에 쓰여진 그대로의 동작을 한다고만 이해하면 될거 같네요.
    /// > accessFlag와 bufferFlag는 기본 설정값을 넣었고, 이외의 설정값을 굳이 알아볼 필요는 없을듯합니다.
    /// > 결국엔 아래의 작업들이 더블 버퍼링을 위한 것인데, 그 개념적 이해만 있으면 될 듯 합니다.
    /// > 더블 버퍼링은 스터디 시간에 좀 더 구두로 설명드릴게요.

	//얘네는 왜 대문자로 쓰지
    /// > DWORD, RECT 등의 윈도우 라이브러리의 클래스는 대체로 대문자로 이름을 지어놓았고, 딱히 이유는 없습니다.
    /// > GENERIC_READ 등의 매크로값(#define)은 보통 대문자_대문자 식으로 이름짓습니다. 이것도 문법적인 이유는 없고, 일종의 약속.
	DWORD accessFlag = GENERIC_READ | GENERIC_WRITE;
	DWORD bufferFlag = CONSOLE_TEXTMODE_BUFFER;
	m_ScreenBuffer[0] = CreateConsoleScreenBuffer(accessFlag, 0, nullptr, bufferFlag, nullptr);
	m_ScreenBuffer[1] = CreateConsoleScreenBuffer(accessFlag, 0, nullptr, bufferFlag, nullptr);
	
	// 커서 인포 세팅
	SetConsoleCursorInfo(m_ScreenBuffer[0], &cci);
	SetConsoleCursorInfo(m_ScreenBuffer[1], &cci);

	// 0번 버퍼를 활성화
	SetConsoleActiveScreenBuffer(m_ScreenBuffer[0]);

	// 현재 백버퍼는 1번 버퍼라는 뜻
	m_BackBufferIdx = 1;
}

void Console::Release()
{
	//핸들 닫기
	CloseHandle(m_ScreenBuffer[0]);
	CloseHandle(m_ScreenBuffer[1]);
}

void Console::Clear()
{
	// 버퍼 내용 지우기
	DWORD dw;
	DWORD screensize = m_ScreenWidth * m_ScreenHeight;
	FillConsoleOutputCharacter(m_ScreenBuffer[m_BackBufferIdx], L' ', screensize, { 0, 0 }, &dw);
}

void Console::SwapBuffer()
{
	// 백버퍼 활성화
	SetConsoleActiveScreenBuffer(m_ScreenBuffer[m_BackBufferIdx]);

	// 백버퍼 인덱스 교체
	switch (m_BackBufferIdx)
	{
		case 0: m_BackBufferIdx = 1; break;
		case 1: m_BackBufferIdx = 0; break;
	}

}

// 문자 하나 표시하기
// 얘는 왜 char& _shape로 안받나요?
/// > char& _shape로 받아도 상관없지만, 굳이 그럴 필요가 없기 때문입니다.
/// > 기본타입(char, int, bool 등)의 경우 복사되는 비용이 레퍼런스로 넘기는 비용과 동일하기 때문.
/// > 하지만 클래스타입(string 등)은 복사비용이 멤버변수에 따라 엄청 커질 수 있기 때문에
/// > 복사할 필요가 없는 이런 구문에선 레퍼런스로 넘기도록 하는 것입니다.
void Console::Print(wchar_t _shape, short _x, short _y)
{
	DWORD dw;

	// 커서 지정 좌표로 이동
	SetConsoleCursorPosition(m_ScreenBuffer[m_BackBufferIdx], { _x, _y });
	
	// 글자 쓰기(shape 표시)
	WriteConsole(m_ScreenBuffer[m_BackBufferIdx], &_shape, 1, &dw, nullptr);
}

// 문자열 표시하기
void Console::PrintText(const std::wstring & _text, short _x, short _y)
{
	DWORD dw;

	SetConsoleCursorPosition(m_ScreenBuffer[m_BackBufferIdx], { _x, _y });
	WriteConsole(m_ScreenBuffer[m_BackBufferIdx], _text.c_str(), _text.length(), &dw, nullptr);
}

RECT Console::GetBoundaryBox() const
{
	// RECT top,left,right,bottom를 멤버변수로 가지는 구조체?
    /// 넹. 그 구현코드가 궁금하면 타입에 커서를 놓고 F12를 누르면 구현코드로 이동합니다.
	RECT boundaryBox;
	boundaryBox.top = 0;
	boundaryBox.left = 0;
	boundaryBox.right = m_ScreenWidth - 2;
	boundaryBox.bottom = m_ScreenHeight - 1;

	// 바운더리 박스 반환
	return boundaryBox;
}
