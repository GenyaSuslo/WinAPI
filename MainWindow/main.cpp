#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include"resource.h"

#define IDC_COMBO	1001
#define IDC_BUTTON_APPLY	1002
CONST CHAR* g_CURSOR[] = { "Zerg.cur", "Protoss.cur", "Terran.cur" };

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

	//=LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_RAM));
	//=LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_CPU));	//Sm - small
	//wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = (HICON)LoadImage(hInstance, "pie_chart_icon_179859.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);				 
	wc.hIconSm = (HICON)LoadImage(hInstance, "idea_light_bulb_icon_179853.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);			
	wc.hCursor = (HCURSOR)LoadImage(hInstance,"Spongebob - Normal Select.ani",IMAGE_CURSOR,LR_DEFAULTSIZE,LR_DEFAULTSIZE,LR_LOADFROMFILE);
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
	static HCURSOR hCursor;
	switch (uMsg)
	{
	case WM_CREATE:
	{
		HWND hCombo = CreateWindowEx
		(
			NULL,
			"ComboBox",
			"",
			WS_CHILD | WS_VISIBLE | CBN_DROPDOWN,
			10, 10,
			200, 200,
			hwnd,
			(HMENU)IDC_COMBO,
			GetModuleHandle(NULL),
			NULL
		);
		for (int i = 0; i < sizeof(g_CURSOR) / sizeof(g_CURSOR[0]); i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)g_CURSOR[i]);
		}
		HWND hMutton = CreateWindowEx
		(
			NULL,
			"Button",
			"Apply",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			220, 10,
			100, 22,
			hwnd,
			(HMENU)IDC_BUTTON_APPLY,
			GetModuleHandle(NULL),
			NULL
		);
	}
	break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
	case IDC_BUTTON_APPLY:
		{
			HWND hCombo = GetDlgItem(hwnd, IDC_COMBO);
			int i = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
			CHAR sz_filename[_MAX_FNAME]{};
			CHAR sz_filepath[_MAX_PATH]= "StarCraftOriginal\\";
			SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)sz_filename);
			strcat(sz_filepath, sz_filename);
			MessageBox(hwnd, sz_filepath, "info", MB_OK);
			HCURSOR hCursor = (HCURSOR)LoadImage
			(
				GetModuleHandle(NULL),
				sz_filepath,
				IMAGE_CURSOR,
				LR_DEFAULTSIZE, LR_DEFAULTSIZE,
				LR_LOADFROMFILE
			);
			//SendMessage(hCombo,WM_SETCURSOR,)
			SetCursor(hCursor);

		}
		break;
	/*case WM_SETCURSOR:
	{
		HWND hCombo = GetDlgItem(hwnd, IDC_COMBO);
		int i = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
		CHAR sz_filename[_MAX_FNAME]{};
		CHAR sz_filepath[_MAX_PATH] = "StarCraftOriginal\\";
		SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)sz_filename);
		strcat(sz_filepath, sz_filename);
		MessageBox(hwnd, sz_filepath, "info", MB_OK);
		HCURSOR hCursor = (HCURSOR)LoadImage
		(
			GetModuleHandle(NULL),
			sz_filepath,
			IMAGE_CURSOR,
			LR_DEFAULTSIZE, LR_DEFAULTSIZE,
			LR_LOADFROMFILE
		);
		SetCursor(hCursor);

	}
	break;*/
	case WM_DESTROY:PostQuitMessage(0);
		break;
	case WM_CLOSE:	DestroyWindow(hwnd);
		break;
	default:		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return NULL;
	};
