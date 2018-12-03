#include "pch.h"
#include "GameManager.h"

void GameManager::Run()
{
	Init();
	MainLoop();
	Release();
}

void GameManager::Shutdown()
{
	m_IsOn = false;
}

void GameManager::Init()
{
	m_IsOn = true;
}

void GameManager::MainLoop()
{
	int loopCount = 0;
	while (m_IsOn)
	{	
		std::cout << "Hello World!\n";

		++loopCount;
		if (loopCount >= 3)
		{
			Shutdown();
		}
	}
}

void GameManager::Release()
{
}



