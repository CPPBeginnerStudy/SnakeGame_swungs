#pragma once
class Console
{

public:
	// �̱��� ������ ����... �ʿ��� �༮...

	// �̱��� ������ ���α׷� �⵿ֱ�� �� �ϳ��� �ν��Ͻ��� ������ ����ϴ� �����̴�.
	// ���� �� ���� �޸� �Ҵ��ϱ� ���� �տ� static�� �ٿ��� ���� ������ �����Ѵ�.
	// ���� ������� �θ��� �� �Ҵ��س��� �޸� ������ �ٲ��� �ʾƼ��� �� ����
    /// > �½��ϴ�!
	// ���� �ν��Ͻ��̱� ������ �ٸ� ��ü���� ����ϱ� ���� �ѹ��� ����� ������ �޸� ���� �����ϴ� ������ �ִٰ� �Ѵ�
	// �޾ƿ��� ������ ���� ���� ������ ::�� ����ؼ� Console::GetInstance() ó�� ����
    /// > �¾ƿ�! ^^)/
    // Console �ν��Ͻ��� ���������� Console.Run(); �̷������� �ν��Ͻ��� ���� �� �Լ��� ����ϴ� �� ����
	// �������� ���� ���·ε� �Լ��� �� ���� ::�� ����ϴ� ���ϴ�.
    /// > �Ź� �Ʒ��� ���� ����ص� �ǰ�,
    /// > Console::GetInstance().Init();
    /// > Console::GetInstance().Release();
    /// > ���۷��� ������ ��� �����Ͽ� ����ص� �˴ϴ�.
    /// > Console& console = Console::GetInstance()
    /// > console.Init();
    /// > console.Release();
    /// > �ᱹ���� GetInstance()�� ��ȯ�ϴ� ���� �ν��Ͻ��� ���� �Լ��� ȣ���ϴ� ���̰�,
    /// > �� �ν��Ͻ��� �Ź� �ٽ� ã�ƿ�����, �ƴϸ� �ѹ� ã�� �� ��� ����� ���̳��� �����Դϴ�.

	// �����Ϳ� �ּҰ� ��ȯ, ���۷���

	// int* pa;
	// int Ÿ�� ������ �ּҰ��� ���� �� �ִ� ������ pa ����
	// *pa ������ pa�� ������, �� pa�� �ּҰ��� ������ ��� �ִ� ���� ��ȯ
	
	// int a;
	// &a a��� ������ �ּҰ��� ��ȯ
	// int &a 
    /// > &�����ڰ� ������ �ּҰ��� ��ȯ�ϴ� ���� ������ ����� ���� �����Դϴ�.
    /// > ��, int* pa = &a; �� ���� a������ ����Ҷ� �տ� &�� ���̸� �� �ּҸ� ��ȯ�ϰ� �Ǵ� ��.
    /// > int &a; ó�� ���� ����ÿ� ���̴� &�� ����Ÿ���̶�� ���� �ٸ� �ǹ̷� ���Դϴ�.
    /// > int &a; �� int& a;�� ���� �����մϴ�. (���⿡ ������� ����)

	// int& a = b;
	// �̹� �̸��� �پ��ִ� ������ �� �ٸ� �̸��� �ٿ��ִ� ��
	// &a �� b�� ������ ����
	// ���� �ּҰ� ��ȯ���� �ٸ� �ǹ��̴�
	// �����͸� �������ϴ� �Ͱ� ����ϴٰ� �Ѵ�
	// �������� �Ű� ������ ���� �����Ϸ��� ��쳪 �Ű� ������ ��� ���纻�� ������ �������� ��� �Լ� �Ű������� ���� ���ȴ�.
    /// > �� �½��ϴ�.

	// �ܼ� �ν��Ͻ��� ������(����?)���� ��ȯ�Ѵ�. 
	// ���� �ܼ� �ν��Ͻ� �������� ���� �ʿ� ���� �Ű� ������ ���� ��ȭ���Ѿ� �ϹǷ�.
	// Console& A = instance; 
	// ���۷��� ���� �����ϱ� �볻 ��ƴ�
    /// > �� �½��ϴ�.. ��_��
	static Console& GetInstance()
	{
		static Console instance;
		return instance;
	}

private:
	// ������� ���� ���ش�
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

	// m_ScreenBuffer��� �̸��� short Ÿ�� 2�� ������ �迭�� �����
	// HANDLE Ÿ���� �������� �ٸ� �̸��̶�� �����ص� �ȴٰ� �Ѵ�

	// �������۸� 
	// ��ũ������ 2���� ����� ����ۿ� ��ü�� �� �׷�����(�������Ǹ�) 
	// ���� ȭ�鿡 ǥ�õ� ���ۿ� ����۸� ���� �����Ͽ� ȭ�鿡 �ѹ��� ǥ�õǵ��� �Ѵ�
	HANDLE m_ScreenBuffer[2];

	// ����� ������ ���� �ε���
	short m_BackBufferIdx;

};
