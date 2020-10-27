#include "stdafx.h"

#include "SceneCenter.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
bool GenerateWindow(HINSTANCE hIns, int nCmdShow, LPWSTR className, LPWSTR windowTitle, UINT windowWidth = 1280, UINT windowHeight = 720);

int WINAPI WinMain(HINSTANCE hIns, HINSTANCE hPrevIns, LPSTR lpCmdLine, int nCmdShow)
{
	SceneCenter sceneCenter;
	if(GenerateWindow(hIns, nCmdShow, L"Win32Window", L"DirectXFramework"))
	{
		MSG msg;
		while(true)
		{
			while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			if(msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				sceneCenter.InputProcess(); // TODO Input처리 어떻게 할지 연구, 논의 필요
				sceneCenter.Update(); // TODO timeProgressRatio 계산 필요
				sceneCenter.Render();
			}
		}
		return msg.wParam;
	}
	return 0;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	break;
	default:
	{
		DefWindowProc(hWnd, message, wParam, lParam);
	}
	break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

bool GenerateWindow(HINSTANCE hIns, int nCmdShow, LPWSTR className, LPWSTR windowTitle, UINT windowWidth, UINT windowHeight)
{
	HWND hWnd;
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(WNDCLASSEX));
	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_HREDRAW | CS_VREDRAW; // HREDARW = 윈도우 세로 변경 시 새로 그림 VREDRAW = 가로
	wcex.lpfnWndProc = WindowProc;
	wcex.hInstance = hIns;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wcex.lpszClassName = className;
	wcex.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

	if (RegisterClassEx(&wcex) == false)
	{
		return false;
	}

	hWnd = CreateWindowEx(NULL, className, windowTitle, WS_OVERLAPPED | WS_BORDER | WS_SYSMENU | WS_MINIMIZEBOX, (GetSystemMetrics(SM_CXSCREEN) - windowWidth) / 2, (GetSystemMetrics(SM_CYSCREEN) - windowHeight) / 2, 
		windowWidth, windowHeight, NULL, NULL, hIns, NULL);
	ShowWindow(hWnd, nCmdShow);
	return true;
}

