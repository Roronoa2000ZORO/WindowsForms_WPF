#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<cstdio>
#include"resource.h"


CONST CHAR* values[] = { "This","is", "my", "Combo", "Box" };


BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//MessageBox(NULL, "ComboBox check", "Info", MB_OK | MB_ICONINFORMATION);
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
		for (size_t i = 0; i < sizeof(values)/sizeof(values[0]); i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)values[i]);
		}
	}
		break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			int i = SendMessage(hCombo, CB_GETCURSEL, 0, 0); // ���������� ����� ���������� �������� ����������� ������
			SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)sz_buffer);

			CHAR sz_massage[SIZE] = {};
			sprintf(sz_massage, "�� ������� ������� � %i, �� ��������� %s", i, sz_buffer);
			MessageBox(hwnd, sz_massage, "INFO", MB_OK | MB_ICONINFORMATION);
		}
		break;
		case IDCANCEL: EndDialog(hwnd, 0);
			break;
		}
	}
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}