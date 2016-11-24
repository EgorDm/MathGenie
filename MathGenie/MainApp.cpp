#include "stdafx.h"
#include "MainApp.h"
#include <string>
#include <cmath>
#include "Hero.h"

MainApp* MainApp::instance = nullptr;

MainApp* MainApp::getInstance()
{
	if (instance == nullptr)
	{
		instance = new MainApp();
	}
	return instance;
}

MainApp::MainApp()
{
}


MainApp::~MainApp()
{
}

void MainApp::start()
{
	AddHook();
}

bool MainApp::OnKeyClick(DWORD keyCode, WPARAM eventType)
{
	switch (keyCode)
	{
	case VK_HOME:
		if (((eventType == WM_KEYUP) || (eventType == WM_SYSKEYUP)))
		{
			exit(0);
		}
		return true;
	case VK_LEFT:
		if (((eventType == WM_KEYUP) || (eventType == WM_SYSKEYUP)))
		{
			currentInput = "";
			interceptInput = true;
		}
		return true;
	case VK_RIGHT:
		if (((eventType == WM_KEYUP) || (eventType == WM_SYSKEYUP)))
		{
			try {
				//SendText((currentInput + "=").c_str());
				auto result = Hero::eval(currentInput);
				
				SendText(dbl2str(result).c_str());
			} catch(std::runtime_error e)
			{
				SendText("[");
			}
			currentInput = "";
			interceptInput = false;
		}
		return true;
	}

	if (!interceptInput) return false;
	switch (keyCode)
	{
	case VK_NUMPAD0:
		if (((eventType == WM_KEYUP) || (eventType == WM_SYSKEYUP))) appendInput("0");
		return true;
	case VK_NUMPAD1:
		if (((eventType == WM_KEYUP) || (eventType == WM_SYSKEYUP))) appendInput("1");
		return true;
	case VK_NUMPAD2:
		if (((eventType == WM_KEYUP) || (eventType == WM_SYSKEYUP))) appendInput("2");
		return true;
	case VK_NUMPAD3:
		if (((eventType == WM_KEYUP) || (eventType == WM_SYSKEYUP))) appendInput("3");
		return true;
	case VK_NUMPAD4:
		if (((eventType == WM_KEYUP) || (eventType == WM_SYSKEYUP))) appendInput("4");
		return true;
	case VK_NUMPAD5:
		if (((eventType == WM_KEYUP) || (eventType == WM_SYSKEYUP))) appendInput("5");
		return true;
	case VK_NUMPAD6:
		if (((eventType == WM_KEYUP) || (eventType == WM_SYSKEYUP))) appendInput("6");
		return true;
	case VK_NUMPAD7:
		if (((eventType == WM_KEYUP) || (eventType == WM_SYSKEYUP))) appendInput("7");
		return true;
	case VK_NUMPAD8:
		if (((eventType == WM_KEYUP) || (eventType == WM_SYSKEYUP))) appendInput("8");
		return true;
	case VK_NUMPAD9:
		if (((eventType == WM_KEYUP) || (eventType == WM_SYSKEYUP))) appendInput("9");
		return true;
	case VK_DECIMAL:
		if (((eventType == WM_KEYUP) || (eventType == WM_SYSKEYUP))) appendInput(".");
		return true;
	case VK_SUBTRACT:
		if (((eventType == WM_KEYUP) || (eventType == WM_SYSKEYUP))) appendInput("-");
		return true;
	case VK_ADD:
		if (((eventType == WM_KEYUP) || (eventType == WM_SYSKEYUP))) appendInput("+");
		return true;
	case VK_MULTIPLY:
		if (((eventType == WM_KEYUP) || (eventType == WM_SYSKEYUP))) appendInput("*");
		return true;
	case VK_DIVIDE:
		if (((eventType == WM_KEYUP) || (eventType == WM_SYSKEYUP))) appendInput("/");
		return true;
	case 0x4D:
		if (((eventType == WM_KEYUP) || (eventType == WM_SYSKEYUP))) appendInput("%");
		return true;
	case 0x42:
		if (((eventType == WM_KEYUP) || (eventType == WM_SYSKEYUP))) appendInput("(");
		return true;
	case 0x4E:
		if (((eventType == WM_KEYUP) || (eventType == WM_SYSKEYUP))) appendInput(")");
		return true;
	}
	return false;
}

DWORD MainApp::MessageLoop(LPVOID)
{
	MSG msg;
	auto appInstance = GetModuleHandle(nullptr);

	SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHook, appInstance, 0);

	while (GetMessage(&msg, nullptr, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT MainApp::KeyboardHook(int nCode, WPARAM wParam, LPARAM lParam)
{
	auto fEatKeystroke = FALSE;
	switch (wParam)
	{
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		auto p = reinterpret_cast<PKBDLLHOOKSTRUCT>(lParam);
		fEatKeystroke = getInstance()->OnKeyClick(p->vkCode, wParam);
	}

	return(fEatKeystroke ? 1 : CallNextHookEx(nullptr, nCode, wParam, lParam));
}

/*if ((wParam == WM_KEYDOWN) || (wParam == WM_SYSKEYDOWN)) // Keydown
{
keybd_event('7', 0, 0, 0);
}
else if ((wParam == WM_KEYUP) || (wParam == WM_SYSKEYUP)) // Keyup
{
keybd_event('7', 0, KEYEVENTF_KEYUP, 0);
}*/

