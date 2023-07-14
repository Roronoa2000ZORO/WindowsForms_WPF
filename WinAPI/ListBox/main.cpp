#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <cstdio>
#include"resource.h"


BOOL CALLBACK DialogProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DialogProcAdd(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
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

        HWND hwndListBox = GetDlgItem(hwnd, IDC_LISTBOX);


        SendMessage(hwndListBox, LB_ADDSTRING, 0, (LPARAM)"Item 1");
        SendMessage(hwndListBox, LB_ADDSTRING, 0, (LPARAM)"Item 2");
        SendMessage(hwndListBox, LB_ADDSTRING, 0, (LPARAM)"Item 3");


        SendMessage(hwndListBox, LB_SETCURSEL, 0, 0);

        return TRUE;
    }
    case WM_COMMAND:
    {
        /*switch (LOWORD(wParam))
        {
        case IDC_ADD:
        {
            DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDC_ADD), hwnd, (DLGPROC)DialogProcAdd, 0);
        }
        break;*/

        if (LOWORD(wParam) == IDC_ADD)
        {
            DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD), hwnd, (DLGPROC)DialogProcAdd, 0);
        }
        else if (LOWORD(wParam) == IDC_DELETE)
        {
            HWND hList = GetDlgItem(hwnd, IDC_LISTBOX);
            SendMessage(hList, LB_DELETESTRING, SendMessage(hList, LB_GETCURSEL, 0, 0), 0);
        }
        else if (LOWORD(wParam) == IDOK)
        {

            HWND hwndListBox = GetDlgItem(hwnd, IDC_LISTBOX);


            INT selectedIndex = SendMessage(hwndListBox, LB_GETCURSEL, 0, 0);


            CONST INT SIZE = 256;
            CHAR selectedItemText[SIZE] = {};
            SendMessage(hwndListBox, LB_GETTEXT, selectedIndex, (LPARAM)selectedItemText);

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
            SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)sz_buffer);
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