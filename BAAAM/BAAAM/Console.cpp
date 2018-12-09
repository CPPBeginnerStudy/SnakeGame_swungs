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

	//얘네는 왜 대문자로 쓰지
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
	FillConsoleOutputCharacter(m_ScreenBuffer[m_BackBufferIdx], ' ', screensize, { 0, 0 }, &dw);
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
void Console::Print(char _shape, short _x, short _y)
{
	DWORD dw;

	// 커서 지정 좌표로 이동
	SetConsoleCursorPosition(m_ScreenBuffer[m_BackBufferIdx], { _x, _y });
	
	// 글자 쓰기(shape 표시)
	WriteConsole(m_ScreenBuffer[m_BackBufferIdx], &_shape, 1, &dw, nullptr);
}

// 문자열 표시하기
void Console::PrintText(const std::string & _text, short _x, short _y)
{
	DWORD dw;

	SetConsoleCursorPosition(m_ScreenBuffer[m_BackBufferIdx], { _x, _y });
	WriteConsole(m_ScreenBuffer[m_BackBufferIdx], _text.c_str(), _text.length(), &dw, nullptr);
}

RECT Console::GetBoundaryBox() const
{
	// RECT top,left,right,bottom를 멤버변수로 가지는 구조체?
	RECT boundaryBox;
	boundaryBox.top = 0;
	boundaryBox.left = 0;
	boundaryBox.right = m_ScreenWidth - 2;
	boundaryBox.bottom = m_ScreenHeight - 1;

	// 바운더리 박스 반환
	return boundaryBox;
}
