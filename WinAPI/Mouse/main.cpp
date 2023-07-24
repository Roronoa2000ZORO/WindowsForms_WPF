#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include<cstdio>
#include <CommCtrl.h>
#include "resource.h"


CONST CHAR g_sz_MY_WINDOW_CLASS[] = "MyFirstWindow";
HWND g_hTooltipWnd = NULL;

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
    //1) ����������� ������ ����:
    WNDCLASSEX wc;
    ZeroMemory(&wc, sizeof(wc));


    wc.cbSize = sizeof(wc);
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;

    wc.style = 0;

    wc.hIcon = (HICON)LoadImage(hInstance, "palm.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
    wc.hIconSm = (HICON)LoadImage(hInstance, "star.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);

    wc.hCursor = (HCURSOR)LoadImage(hInstance, "sccpointer.ani", IMAGE_CURSOR, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

    wc.hInstance = hInstance;
    wc.lpfnWndProc = (WNDPROC)WndProc;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = g_sz_MY_WINDOW_CLASS;

    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "����� �� ���������������", "Error", MB_OK | MB_ICONERROR);
        return 0;
    }

    //2) �������� ����:

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    int newWidth = screenWidth * 3 / 4;
    int newHeight = screenHeight * 3 / 4;

    HWND hwnd = CreateWindowEx(
        0,
        g_sz_MY_WINDOW_CLASS,   //��� ������ ����
        g_sz_MY_WINDOW_CLASS,   //��������� ����
        WS_OVERLAPPEDWINDOW, //����� ���� ��� �������� ���� ��������� ������ ����� WS_OVERLAPPEDWINDOW - ��� ���� �������� ������(TOP_LEVEL_WINDOW), ������� �������� � ���� �������� ....
        (screenWidth - newWidth) / 2, (screenHeight - newHeight) / 2, //������������� ���� �� ������
        newWidth, newHeight, //������ ����
        NULL, //Parent Window
        NULL, //��� �������� ���� ��� ����. ��� ��������� ���� ��� ID ��� ������� (IDC_EDIT)
        hInstance,
        NULL);

    if (hwnd == 0)
    {
        MessageBox(NULL, "���� �� ���� �������", "Error", MB_OK | MB_ICONERROR);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow); // ������ ����� ����������� ����
    UpdateWindow(hwnd); // ��������� ���������� ����


    g_hTooltipWnd = CreateWindowEx(
        NULL, 
        TOOLTIPS_CLASS, 
        NULL,
        WS_POPUP | TTS_ALWAYSTIP | TTS_NOFADE | TTS_NOANIMATE,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        hwnd, 
        NULL, 
        hInstance,
        NULL);

    if (g_hTooltipWnd)
    {
        TOOLINFO toolInfo = { sizeof(toolInfo) };
        toolInfo.uFlags = TTF_SUBCLASS | TTF_ABSOLUTE;
        toolInfo.hwnd = hwnd;
        toolInfo.hinst = hInstance;
        toolInfo.uId = 0;
        GetClientRect(hwnd, &toolInfo.rect);
        SendMessage(g_hTooltipWnd, TTM_ADDTOOL, 0, (LPARAM)&toolInfo);
    }
    //3) ������ ����� ���������:

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg); // ����������� ��������� ����������� ������ � ���������� ���������
        DispatchMessage(&msg); // ���������� ��������� ��������� ����. ��������� ����� �� GetMessage();
    }

    return msg.wParam;
}

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    POINT cursorPos;
    RECT windowRect;

    switch (uMsg)
    {
    case WM_CREATE:
        GetWindowRect(hwnd, &windowRect);
        break;
    case WM_COMMAND:
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_MOUSEMOVE:
    {
        
        cursorPos.x = LOWORD(lParam);
        cursorPos.y = HIWORD(lParam);

        CONST INT SIZE = 256;
        CHAR sz_buffer[SIZE] = {};
        sprintf(sz_buffer, ("Mouse Position: %ix%i"), cursorPos.x, cursorPos.y);

        TOOLINFO toolInfo = { sizeof(toolInfo) };
        toolInfo.hwnd = hwnd;
        toolInfo.hinst = GetModuleHandle(NULL);
        toolInfo.uId = 0;
        toolInfo.lpszText = sz_buffer;
        GetClientRect(hwnd, &toolInfo.rect);

        SendMessage(g_hTooltipWnd, TTM_UPDATETIPTEXT, 0, (LPARAM)&toolInfo);

    }break;
    default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}