#include<Windows.h>
#include"resource.h"

#define IDC_EDIT	1003
#define IDC_BUTTON	1002

CONST CHAR g_sz_CALC[] = "Calc";

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.cbSize = sizeof(wc);
	wc.cbWndExtra = 0;
	wc.cbClsExtra = 0;
	wc.style = 0;

	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground = HBRUSH(COLOR_WINDOW + 2);
	
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_sz_CALC; 
	
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class Registration failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	INT screen_width = GetSystemMetrics(SM_CXSCREEN);
	INT screen_height = GetSystemMetrics(SM_CYSCREEN);
	INT window_width = screen_width * 0.16;
	INT window_height = screen_height * 0.35;
	INT start_x = screen_width / 8;
	INT start_y = screen_height / 8;

	HWND hwnd = CreateWindowEx
	(
		NULL,
		g_sz_CALC,
		g_sz_CALC,
		WS_OVERLAPPEDWINDOW,
		start_x, start_y,
		window_width, window_height,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Windows Creation Failed", "Error", MB_OK | MB_ICONINFORMATION);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		HWND hEdit = CreateWindowEx
		(
			NULL,
			"Edit",
			"input",
			WS_CHILD | WS_VISIBLE|ES_CENTER,
			10, 20,
			250, 30,
			hwnd,
			(HMENU)IDC_EDIT,
			GetModuleHandle(NULL),
			NULL
		);
		for (int i = 0; i < 3; i++)
		{
			int x_pos = 0;
			int y_pos = 65;
			HWND hButoon = CreateWindowEx
		(
			NULL,
			"Button",
			"1",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			x_pos+=y_pos, 60,
			50, 40,
			hwnd,
			(HMENU)IDC_BUTTON,
			GetModuleHandle(NULL),
			NULL
		);
		}
		
		/*HWND hButoon = CreateWindowEx
		(
			NULL,
			"Button",
			"2",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			70, 60,
			50, 40,
			hwnd,
			(HMENU)IDC_BUTTON,
			GetModuleHandle(NULL),
			NULL
		);*/
	}
	break;
	case WM_COMMAND:
		break;
	case WM_DESTROY:PostQuitMessage(0);
		break;
	case WM_CLOSE: DestroyWindow(hwnd);
		break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return NULL;

}