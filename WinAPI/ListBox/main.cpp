#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <cstdio>
#include"resource.h"
#include"Winuser.h"


BOOL CALLBACK DialogProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DialogProcAdd(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{

    //HWND hwnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG), NULL, DialogProc);
    DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG), NULL, (DLGPROC)DialogProc, 0);

    return 0;
}


BOOL CALLBACK DialogProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_INITDIALOG:
    {

        HWND hListBox = GetDlgItem(hwnd, IDC_LISTBOX);

        SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)"Smit");
        SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)"Jony");
        SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)"Lara");
        SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)"Adam");

        SendMessage(hListBox, LB_SETCURSEL, 0, 0);
        SendMessage(hListBox, LBS_SORT, 0, 0);

        return TRUE;
    }
    case WM_COMMAND:
    {
        HWND hListBox = GetDlgItem(hwnd, IDC_LISTBOX);

        if (LOWORD(wParam) == IDC_SORT)
        {
            HWND hsort = GetDlgItem(hwnd, IDC_SORT);

            if (SendMessage(hsort, BM_GETCHECK, 0, 0) == BST_CHECKED)
                SendMessage(hListBox, LBS_SORT, 0, 0);
            else
                SendMessage(hListBox, LB_SETSEL, (WPARAM)FALSE, (LPARAM)-1);
        }
        else if (LOWORD(wParam) == IDC_ADD)
        {
            DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD), hwnd, (DLGPROC)DialogProcAdd, 0);
        }
        else if (LOWORD(wParam) == IDC_DELETE)
        {
            SendMessage(hListBox, LB_DELETESTRING, SendMessage(hListBox, LB_GETCURSEL, 0, 0), 0);
        }
        else if (LOWORD(wParam) == IDOK)
        {

            INT selectedIndex = SendMessage(hListBox, LB_GETCURSEL, 0, 0);


            CONST INT SIZE = 256;
            CHAR selectedItemText[SIZE] = {};
            SendMessage(hListBox, LB_GETTEXT, selectedIndex, (LPARAM)selectedItemText);

            CHAR sz_message[SIZE] = {};
            sprintf(sz_message, "Selected Item:\nIndex: %d\nValue: %s", selectedIndex, selectedItemText);
            MessageBox(hwnd, sz_message, "Selected Item", MB_OK | MB_ICONINFORMATION);

            EndDialog(hwnd, 0);
        }
        else if (LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hwnd, 0);
        }

        return TRUE;
    }
    break;
    case WM_CLOSE:
    {
        EndDialog(hwnd, 0);
        return TRUE;
    }
    }
    return FALSE;
}

BOOL CALLBACK DialogProcAdd(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_INITDIALOG:
        break;
    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case IDOK:
        {
            CONST INT SIZE = 256;
            CHAR sz_buffer[SIZE] = {};
            SendMessage(GetDlgItem(hwnd, IDC_EDIT_ADD), WM_GETTEXT, SIZE, (LPARAM)sz_buffer);

            HWND hParent = GetParent(hwnd);
            HWND hList = GetDlgItem(hParent, IDC_LISTBOX);


            if(sz_buffer[0] == NULL) // Проверка на пустой ввод
                MessageBox(hwnd, "Строка пустая", "Error", MB_OK | MB_ICONINFORMATION);
            else if(LB_ERR == SendMessage(hList, LB_FINDSTRINGEXACT, 0, (LPARAM)sz_buffer))// Проверка на уникальность введенного текста
                SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)sz_buffer);
            else
                MessageBox(hwnd, "Такая строка существует!", "Error", MB_OK | MB_ICONINFORMATION);

            EndDialog(hwnd, 0);
        }
        case IDCANCEL: EndDialog(hwnd, 0);
            break;
        }
    }
    break;
    case WM_CLOSE: EndDialog(hwnd, 0);
    }
    return FALSE;
}
