#pragma once
#include <Windows.h>
#include <utility>

class KeyboardHook
{
private:
	HANDLE hMessageLoop;
	// KeyboardHook* pKeyboardHook;
public:

	KeyboardHook()
	{

	}

	static void GetInstance()
	{
		/*if (pKeyboardHook == nullptr)
			pKeyboardHook = new KeyboardHook();

		return pKeyboardHook;*/
		(new KeyboardHook())->Start();
	}

	void Start()
	{
		this->hMessageLoop = CreateThread(nullptr, NULL, KeyboardHook::MessageLoop, nullptr, NULL, nullptr);
	}

	void End()
	{
		TerminateThread(this->hMessageLoop, 0);
	}

	HANDLE GetThread()
	{
		return hMessageLoop;
	}

	static DWORD WINAPI MessageLoop(LPVOID)
	{
		
	}

	static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
	{
		
	};
};