#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include"resource.h"
#include<vector>
#include<string>

#define IDC_COMBO	1001
#define IDC_BUTTON_APPLY	1002
CONST CHAR* g_CURSOR[] = { "Zerg.cur", "Protoss.cur", "Terran.cur" };

CONST CHAR g_sz_WINDOW_CLASS[] = "My Window Class"; //имя класса окна
std::vector<std::string> LoadCursorFromDir(const std::string& directori);
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
		INT screen_width = GetSystemMetrics(SM_CXSCREEN);
		INT screen_height = GetSystemMetrics(SM_CYSCREEN);
		//CHAR sz_msg[MAX_PATH]{};
		//sprintf(sz_msg, "Resolution: %ix%i", screen_width, screen_height);
		//MessageBox(NULL, sz_msg, "Screen resolution", MB_OK);
		INT window_width = screen_width * 3 / 4;
		INT window_height = screen_height * 3 / 4;

		INT start_x = screen_width / 8;
		INT start_y = screen_height / 8;
		
	HWND hwnd = CreateWindowEx	//в google пишем CreateWindowEx - LearnMicrosoft.Com
	(
		NULL,					//ExStyle
		g_sz_WINDOW_CLASS,		//ClassName
		g_sz_WINDOW_CLASS,		//Window Name
		WS_OVERLAPPEDWINDOW,	//у главного окна всегда будет такой стиль
		start_x, start_y,	//Position - положение окна на экране
		window_width, window_height,	//Size - размер окна на экране
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
			WS_CHILD | WS_VISIBLE |CBS_DROPDOWN| WS_VSCROLL,
			10, 10,
			200, 200,
			hwnd,
			(HMENU)IDC_COMBO,
			GetModuleHandle(NULL),
			NULL
		);
		/*for (int i = 0; i < sizeof(g_CURSOR) / sizeof(g_CURSOR[0]); i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)g_CURSOR[i]);
		}*/
		std::vector<std::string>cursor = LoadCursorFromDir("StarCraftOriginal\\*");
		for (int i = 0; i < cursor.size();i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)cursor[i].c_str());
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
	case WM_SIZE:
	case WM_MOVE:
	{
		RECT rect;
		GetWindowRect(hwnd, &rect);
		CHAR sz_message[MAX_PATH]{};
		sprintf(
			sz_message, "%s - Position: %ix%i, Size: %ix%i",
			g_sz_WINDOW_CLASS, rect.left, rect.top,
			rect.right-rect.left, rect.bottom-rect.top
		);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_message);

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
			//MessageBox(hwnd, sz_filepath, "info", MB_OK);
			//HCURSOR 
			hCursor = (HCURSOR)LoadImage
			(
				GetModuleHandle(NULL),
				sz_filepath,
				IMAGE_CURSOR,
				LR_DEFAULTSIZE, LR_DEFAULTSIZE,
				LR_LOADFROMFILE
			);
			SetClassLong(hwnd, GCLP_HCURSOR, (LONG)hCursor);
			SetClassLong(GetDlgItem(hwnd,IDC_BUTTON_APPLY), GCLP_HCURSOR, (LONG)hCursor);
			SetClassLong(GetDlgItem(hwnd,IDC_COMBO), GCLP_HCURSOR, (LONG)hCursor);
			//SendMessage(hCombo,WM_SETCURSOR,)
			//SetCursor(hCursor);
			return FALSE;

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
std::vector<std::string> LoadCursorFromDir(const std::string& directori)
{
	WIN32_FIND_DATA data;
	std::vector<std::string>files;
	for (
		HANDLE hFind = FindFirstFile(directori.c_str(), &data);
		FindNextFile(hFind, &data);
		)
	{
		//const char* std::string::c.str() возвращает С-string хранящийся в объекте std::string
		if (
			strcmp(strrchr(data.cFileName, '.'), ".cur") == 0||
			strcmp(strrchr(data.cFileName, '.'), ".ani") == 0
		)
			files.push_back(data.cFileName);
	}
	return files;



}
