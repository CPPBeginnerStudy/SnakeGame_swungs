#pragma once
class Console
{

public:
	static Console& GetInstance()
	{
		static Console instance;
		return instance;
	}

// �̱��� ������ ����... �ʿ��� �༮... 
private:
	Console();
	~Console();

};

