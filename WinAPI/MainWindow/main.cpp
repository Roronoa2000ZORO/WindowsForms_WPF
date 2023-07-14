#include<Windows.h>

CONST CHAR g_sz_MY_WINDOW_CLASS[] = "MyFirstWindow";

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
    //1) ����������� ������ ����:
    WNDCLASSEX wc;
    ZeroMemory(&wc, sizeof(wc));

    //������ ������ � ������ (cb - Count Bytes)
    wc.cbSize = sizeof(wc);

    //Class Extra Bytes ���. ����� ������
    wc.cbClsExtra = 0;

    //Window Extra Bytes ���. ����� ����
    wc.cbWndExtra = 0; 

    // �����
    wc.style = 0;


    wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);
    wc.hCursor = LoadIcon(hInstance, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;


    wc.hInstance = hInstance;
    wc.lpfnWndProc = (WNDPROC)WndProc; //TODO: ������� ��������� ����
    wc.lpszMenuName = NULL;
    wc.lpszClassName = g_sz_MY_WINDOW_CLASS;


    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "����� �� ���������������", "Error", MB_OK | MB_ICONERROR);
        return 0;
    }

    //2) �������� ����:
    
    HWND hwnd = CreateWindowEx(
        0,
        g_sz_MY_WINDOW_CLASS,   //��� ������ ����
        g_sz_MY_WINDOW_CLASS,   //��������� ����
        WS_OVERLAPPEDWINDOW, //����� ���� ��� �������� ���� ��������� ������ ����� WS_OVERLAPPEDWINDOW - ��� ���� �������� ������(TOP_LEVEL_WINDOW), ������� �������� � ���� �������� ....
        CW_USEDEFAULT,CW_USEDEFAULT, //��������� �������� ����
        CW_USEDEFAULT,CW_USEDEFAULT, //������ ����
        NULL, //Parent Window
        NULL, //��� �������� ���� ��� ����. ��� ��������� ���� ��� ID ��� ������� (IDC_EDIT)
        hInstance,
        NULL);
    
    if (hwnd == 0)
    {
        MessageBox(NULL, "���� �� ���� ��������", "Error", MB_OK | MB_ICONERROR);
        return 0;
    }
    //3) ������ ����� ���������:

    MSG msg;
    while (GetMessage(&msg, NULL, 0 , 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
    switch (uMsg)
    {
    case WM_CREATE:
        break;
    case WM_COMMAND:
        break;
    case WM_DESTROY: PostQuitMessage(0); break;
    case WM_CLOSE: DestroyWindow(hwnd); break;
    default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }


    return 0;
}