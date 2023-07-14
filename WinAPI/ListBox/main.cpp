#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <cstdio>
#include"resource.h"


INT_PTR CALLBACK DialogProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    
    //HWND hwnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG), NULL, DialogProc);
    DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG), NULL, DialogProc, 0);

    return 0;
}


INT_PTR CALLBACK DialogProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
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
        if (LOWORD(wParam) == IDOK)
        {
            
            HWND hwndListBox = GetDlgItem(hwnd, IDC_LISTBOX);

            
            int selectedIndex = SendMessage(hwndListBox, LB_GETCURSEL, 0, 0);

            
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
    case WM_CLOSE:
    {
        EndDialog(hwnd, 0);
        return TRUE;
    }
    }

    return FALSE;
}