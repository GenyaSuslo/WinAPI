#include<Windows.h>
#include"resource.h"
BOOL CALLBACK DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LRESULT)hIcon);
		HWND hLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		SetFocus(GetDlgItem(hwnd, IDC_EDIT_LOGIN));//установка курсора в окно 'Login'
		
		SetDlgItemTextA(hwnd, IDC_EDIT_LOGIN, "Введите имя пользователя");
		//CHAR privet[] = {"Введите имя пользователя:"};
		//SendMessage(hwnd, IDC_EDIT_LOGIN, EN_CHANGE,(LPARAM)privet);
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_COPY:
		{
			//1)создаем буффер чтения:
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			//2) получаем обработчик окна текстовых полей 'Login' 'Password'
			HWND hLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);//функция GetDlgItem() по ID-ресурса дочернего окна возвращает HWND соответсвующего дочернего окна
			HWND hPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			HWND h1Password = GetDlgItem(hwnd, IDC_STATIC_PASWORD);
			//3)читаем текст из текстового поля
			SendMessage(hLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			//4) загружаем содержимое текстового буфера в поле 'Password'
			SendMessage(hPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			SendMessage(h1Password, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
			break;
		case IDOK: MessageBox(hwnd, "Была нажата кнопка ОК", "Info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL: EndDialog(hwnd, 0);
		}
		break;
	case WM_CLOSE:EndDialog(hwnd, 0);
	}
	return FALSE;
}