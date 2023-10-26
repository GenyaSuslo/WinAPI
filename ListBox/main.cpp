#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include"resource.h"
#include<cstdio>

CONST CHAR* g_sz_VALUES[] = {"This", "is", "my", "first", "List", "Box"};
BOOL CALLBACK DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProc1(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInsatance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShhow)
{
	DialogBoxParam(hInsatance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		{
			HWND hList = GetDlgItem(hwnd, IDC_LIST1);
			for (int i = 0; i<sizeof(g_sz_VALUES) / sizeof(g_sz_VALUES[0]); i++)
			{
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)g_sz_VALUES[i]);
			}
			SetFocus(GetDlgItem(hwnd, IDC_EDIT1));
		}
		break;
	case WM_COMMAND:
		{
			switch LOWORD(wParam)
			{
			case IDOK:
				{
					CONST INT SIZE = 256;
					CHAR sz_buffer[SIZE] = {};
					HWND hList = GetDlgItem(hwnd, IDC_LIST1);
					int i = SendMessage(hList, LB_GETCURSEL, 0, 0);
					SendMessage(hList, LB_GETTEXT, i, (LPARAM)sz_buffer);
					CHAR sz_message[SIZE]{};
					sprintf(sz_message, "Вы выбрали элемент № %i, со значением \"%s\"", i, sz_buffer);
					MessageBox(hwnd, sz_message, "info", MB_OK | MB_ICONINFORMATION);
				}
				break;
			case IDC_LIST1:
			{
				if (HIWORD(wParam) == LBN_DBLCLK)SendMessage(hwnd, WM_COMMAND, IDOK, 0);
				break;
			}
			case IDC_BUTTON_ADD:
			{
				
				CONST INT SIZE = 256;
				CHAR sz_buffer[SIZE]{};
				HWND text = GetDlgItem(hwnd, IDC_EDIT1);
				HWND list = GetDlgItem(hwnd, IDC_LIST1);
				SendMessage(text, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
				SendMessageA(list, LB_ADDSTRING, 0, (LPARAM)sz_buffer);


			}
			break;
			case IDC_BUTTON_DELETE:
			{
				CONST INT SIZE = 256;
				HWND list = GetDlgItem(hwnd, IDC_LIST1);
				int i = SendMessage(list, LB_GETCURSEL, 0, 0);
				CHAR sz_buffer[SIZE]{};
				SendMessage(list, LB_GETTEXT, i, (LPARAM)sz_buffer);
				CHAR sz_message[SIZE]{};
				sprintf(sz_message, "Вы удаляете элемент № %i, значение \"%s\"", i, sz_buffer);
				if(MessageBox(hwnd, sz_message,"info",MB_OKCANCEL|MB_ICONWARNING)==1)
				SendMessage(list, LB_DELETESTRING, i, 0);
			}
			break;
			case IDCANCEL:EndDialog(hwnd, 0);
				break;
			}
		}
		break;
	case WM_CLOSE:EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}
//BOOL CALLBACK DlgProc1(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//	switch (uMsg)
//	{
//		case WM_INITDIALOG:
//			break;
//
//		case WM_COMMAND:
//		{
//			switch LOWORD(wParam)
//			{
//			case IDOK:
//			{
//
//			}
//				break;
//			case IDCANCEL:EndDialog(hwnd, 0);
//				break;
//			}
//		}
//
//		case WM_CLOSE:EndDialog(hwnd, 0);
//			break;
//	}
//	return FALSE;
//}