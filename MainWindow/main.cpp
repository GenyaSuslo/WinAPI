#include<Windows.h>
#include"resource.h"

CONST CHAR g_sz_WINDOW_CLASS[] = "My Window Class"; //имя класса окна
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{	
	//1) Регистрация класса окна
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));
	
	wc.cbSize = sizeof(wc);
	//cb - count bytes (Количество байт)
	wc.cbWndExtra = 0;	//Дополнительные байты окна
	wc.cbClsExtra = 0;	//Дополнительные Байты класса окна
	wc.style = 0;	//Стиль окна

	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_RAM));
	wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_CPU));	//Sm - small
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = HBRUSH(COLOR_WINDOW + 1);

	wc.hInstance = hInstance; //hInstance - экземпляр исполняемого файла программы в памяти
	//Функция WinMain() принимает hInstance как параметр, по этому к нему есть прямой доступ,
	//В любой другой функции hInstance всегда можно получить при помощи функции GetModuleHandle(NULL)
	wc.lpfnWndProc = WndProc;	//указатель на процедуру окна
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_sz_WINDOW_CLASS;

		if (!RegisterClassEx(&wc))
		{
			MessageBox(NULL, "Class Registration failed", "Error", MB_OK | MB_ICONERROR);
			return 0;
		}

	//2)Создание окна
	HWND hwnd = CreateWindowEx	//в google пишем CreateWindowEx - LearnMicrosoft.Com
	(
		NULL,					//ExStyle
		g_sz_WINDOW_CLASS,		//ClassName
		g_sz_WINDOW_CLASS,		//Window Name
		WS_OVERLAPPEDWINDOW,	//у главного окна всегда будет такой стиль
		CW_USEDEFAULT, CW_USEDEFAULT,	//Position - положение окна на экране
		CW_USEDEFAULT, CW_USEDEFAULT,	//Size - размер окна на экране
		NULL,					// Parent window - родительское окно
		//____________
		NULL,	 //hMenu для главного окна этот параметр содержит ID_ресурса меню
				//для дочернего окна, которое является элементом другого окна, в hMenu передается ID_ресурса этого элемента
		//_____________
		hInstance,
		NULL
	);
		if (hwnd == NULL)
		{
			MessageBox(NULL, "Windows Creation Failed", "ERROR", MB_OK | MB_ICONERROR);
			return 0;
		}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	//3) Запуск цикла сообщений
	MSG msg;
		while(GetMessage(&msg, 0, 0, 0)>0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		return msg.wParam;

		

		
}
//------------------------------------------
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON_LAMP));
		HICON hIconSm = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON_PIE));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);

	}
	break;
	case WM_COMMAND:
		break;
	case WM_DESTROY:PostQuitMessage(0);
		break;
	case WM_CLOSE:	DestroyWindow(hwnd);
		break;
	default:		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return NULL;
	};
