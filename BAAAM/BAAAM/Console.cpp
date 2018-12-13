#include "pch.h"
#include "Console.h"

// ������ - �ܼ� �ν��Ͻ��� ������ �� �ڵ����� ȣ��
// ���ڰ� �ִ� �����ڵ� ������ �� �ִٰ� �Ѵ�
// ��� �������൵ ����Ʈ �����ڴ� ȣ���Ѵٰ� �Ѵ�..
Console::Console()
	: m_ScreenWidth(0)
	, m_ScreenHeight(0)
	, m_BackBufferIdx(0)
{
	// ��������
	m_ScreenBuffer[0] = nullptr;
	m_ScreenBuffer[1] = nullptr;
}

// �Ҹ��� - �ܼ� �ν��Ͻ��� �Ҹ��� �� �ڵ����� ȣ�� 
Console::~Console()
{
}

void Console::Init()
{
	// system - �Ű� ������ ���޹��� Ŀ�ǵ带 �����ϴ� �Լ�.
	// ��... Ŀ�ǵ�� �����ϱ� �׳� ���ڿ� ����ϰ� ��������
    /// > system�Լ��� cmdâ���� ���� ��ɾ� ġ�°Ͱ� �����ϰ� ��ɾ �����Ű�� �Լ��Դϴ�.
    /// > �Ʒ��� mode�� �ܼ� Ŀ�ǵ��̸�, ������ cmdâ�� ��� �����ϰ� ġ�� �ܼ�â ũ�Ⱑ ����˴ϴ�.
	system("mode con: lines=30 cols=90");

	//cmdâ ũ�� ����(30����, 90����)
	m_ScreenWidth = 90;
	m_ScreenHeight = 30;

	// Ŀ�� ������ ���Ÿ� ���� �ɼ�
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = FALSE;

	// ��ũ������ 2�� ���� �� �ʱ�ȭ
	// �Ʒ� ������ ���� ���ص� ��?
    /// > �Ŀ�...�밭.. �� �Լ����� �� �Լ��� ������ �״���� ������ �Ѵٰ� �����ϸ� �ɰ� ���׿�.
    /// > accessFlag�� bufferFlag�� �⺻ �������� �־���, �̿��� �������� ���� �˾ƺ� �ʿ�� �������մϴ�.
    /// > �ᱹ�� �Ʒ��� �۾����� ���� ���۸��� ���� ���ε�, �� ������ ���ظ� ������ �� �� �մϴ�.
    /// > ���� ���۸��� ���͵� �ð��� �� �� ���η� ����帱�Կ�.

	//��״� �� �빮�ڷ� ����
    /// > DWORD, RECT ���� ������ ���̺귯���� Ŭ������ ��ü�� �빮�ڷ� �̸��� ������Ұ�, ���� ������ �����ϴ�.
    /// > GENERIC_READ ���� ��ũ�ΰ�(#define)�� ���� �빮��_�빮�� ������ �̸������ϴ�. �̰͵� �������� ������ ����, ������ ���.
	DWORD accessFlag = GENERIC_READ | GENERIC_WRITE;
	DWORD bufferFlag = CONSOLE_TEXTMODE_BUFFER;
	m_ScreenBuffer[0] = CreateConsoleScreenBuffer(accessFlag, 0, nullptr, bufferFlag, nullptr);
	m_ScreenBuffer[1] = CreateConsoleScreenBuffer(accessFlag, 0, nullptr, bufferFlag, nullptr);
	
	// Ŀ�� ���� ����
	SetConsoleCursorInfo(m_ScreenBuffer[0], &cci);
	SetConsoleCursorInfo(m_ScreenBuffer[1], &cci);

	// 0�� ���۸� Ȱ��ȭ
	SetConsoleActiveScreenBuffer(m_ScreenBuffer[0]);

	// ���� ����۴� 1�� ���۶�� ��
	m_BackBufferIdx = 1;
}

void Console::Release()
{
	//�ڵ� �ݱ�
	CloseHandle(m_ScreenBuffer[0]);
	CloseHandle(m_ScreenBuffer[1]);
}

void Console::Clear()
{
	// ���� ���� �����
	DWORD dw;
	DWORD screensize = m_ScreenWidth * m_ScreenHeight;
	FillConsoleOutputCharacter(m_ScreenBuffer[m_BackBufferIdx], L' ', screensize, { 0, 0 }, &dw);
}

void Console::SwapBuffer()
{
	// ����� Ȱ��ȭ
	SetConsoleActiveScreenBuffer(m_ScreenBuffer[m_BackBufferIdx]);

	// ����� �ε��� ��ü
	switch (m_BackBufferIdx)
	{
		case 0: m_BackBufferIdx = 1; break;
		case 1: m_BackBufferIdx = 0; break;
	}

}

// ���� �ϳ� ǥ���ϱ�
// ��� �� char& _shape�� �ȹ޳���?
/// > char& _shape�� �޾Ƶ� ���������, ���� �׷� �ʿ䰡 ���� �����Դϴ�.
/// > �⺻Ÿ��(char, int, bool ��)�� ��� ����Ǵ� ����� ���۷����� �ѱ�� ���� �����ϱ� ����.
/// > ������ Ŭ����Ÿ��(string ��)�� �������� ��������� ���� ��û Ŀ�� �� �ֱ� ������
/// > ������ �ʿ䰡 ���� �̷� �������� ���۷����� �ѱ⵵�� �ϴ� ���Դϴ�.
void Console::Print(wchar_t _shape, short _x, short _y)
{
	DWORD dw;

	// Ŀ�� ���� ��ǥ�� �̵�
	SetConsoleCursorPosition(m_ScreenBuffer[m_BackBufferIdx], { _x, _y });
	
	// ���� ����(shape ǥ��)
	WriteConsole(m_ScreenBuffer[m_BackBufferIdx], &_shape, 1, &dw, nullptr);
}

// ���ڿ� ǥ���ϱ�
void Console::PrintText(const std::wstring & _text, short _x, short _y)
{
	DWORD dw;

	SetConsoleCursorPosition(m_ScreenBuffer[m_BackBufferIdx], { _x, _y });
	WriteConsole(m_ScreenBuffer[m_BackBufferIdx], _text.c_str(), _text.length(), &dw, nullptr);
}

RECT Console::GetBoundaryBox() const
{
	// RECT top,left,right,bottom�� ��������� ������ ����ü?
    /// ��. �� �����ڵ尡 �ñ��ϸ� Ÿ�Կ� Ŀ���� ���� F12�� ������ �����ڵ�� �̵��մϴ�.
	RECT boundaryBox;
	boundaryBox.top = 0;
	boundaryBox.left = 0;
	boundaryBox.right = m_ScreenWidth - 2;
	boundaryBox.bottom = m_ScreenHeight - 1;

	// �ٿ���� �ڽ� ��ȯ
	return boundaryBox;
}
