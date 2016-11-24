#pragma once
#include <Windows.h>
#include <winuser.h>
#include <string>
using namespace std;

class MainApp
{
private:
	static MainApp* instance;
	HANDLE hMessageLoop;

	bool OnKeyClick(DWORD keyCode, WPARAM eventType);

	bool interceptInput = true;
	std::string currentInput = "";

public:
	
	static MainApp* getInstance();
	static DWORD WINAPI MessageLoop(LPVOID);
	static LRESULT CALLBACK KeyboardHook(int nCode, WPARAM wParam, LPARAM lParam);
	static void GenerateKey(BYTE vk)
	{
		INPUT Input[2];
		ZeroMemory(&Input, sizeof(Input));
		Input[0].type = INPUT_KEYBOARD;
		Input[0].ki.dwFlags = KEYEVENTF_EXTENDEDKEY;
		Input[0].ki.wVk = vk;
		Input[0].ki.dwFlags = 0;

		Input[1].type = INPUT_KEYBOARD;
		Input[1].ki.dwFlags = KEYEVENTF_EXTENDEDKEY;
		Input[1].ki.wVk = vk;
		Input[1].ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(2, Input, sizeof(INPUT));
		return;
	}
	static void SendText(const char *szText)
	{
		for (auto i = 0; i<strlen(szText); i++)
		{
			GenerateKey(static_cast<UCHAR>(VkKeyScan(szText[i])));
			Sleep(60);
		}
	}

	MainApp();
	~MainApp();
	void start();

	void AddHook()
	{
		this->hMessageLoop = CreateThread(nullptr, NULL, MessageLoop, nullptr, NULL, nullptr);
	}
	void RemoveHook()
	{
		TerminateThread(this->hMessageLoop, 0);
	}
	HANDLE GetThread()
	{
		return hMessageLoop;
	}

	void appendInput(std::string append)
	{
		currentInput.append(append);
	}
	double getCurrentInput()
	{
		return std::stod(currentInput);
	}

	static std::string dbl2str(double d)
	{
		size_t len = std::snprintf(0, 0, "%.10f", d);
		std::string s(len + 1, 0);
		// technically non-portable, see below
		std::snprintf(&s[0], len + 1, "%.10f", d);
		// remove nul terminator
		s.pop_back();
		// remove trailing zeros
		s.erase(s.find_last_not_of('0') + 1, std::string::npos);
		// remove trailing point
		if (s.back() == '.') {
			s.pop_back();
		}
		return s;
	}
};
