#include<Windows.h>
#include"resource.h"

CONST CHAR g_sz_MY_WINDOW_CLASS[] = "MyFirstWindow";

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
    //1) Регистрация класса окна:
    WNDCLASSEX wc;
    ZeroMemory(&wc, sizeof(wc));

    //Размер класса в Байтах (cb - Count Bytes)
    wc.cbSize = sizeof(wc);

    //Class Extra Bytes Доп. Байты классы
    wc.cbClsExtra = 0;

    //Window Extra Bytes Доп. Байты окна
    wc.cbWndExtra = 0; 

    // Стиль
    wc.style = 0;


    //wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_PALM));
    //wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_STAR));
    wc.hIcon =   (HICON)LoadImage(hInstance, "palm.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
    wc.hIconSm = (HICON)LoadImage(hInstance, "star.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);


    wc.hCursor = (HCURSOR)LoadImage(hInstance, "sccpointer.ani", IMAGE_CURSOR, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;


    wc.hInstance = hInstance;
    wc.lpfnWndProc = (WNDPROC)WndProc; //TODO: Указать процедуру окна
    wc.lpszMenuName = NULL;
    wc.lpszClassName = g_sz_MY_WINDOW_CLASS;


    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Класс не зарегистрирован", "Error", MB_OK | MB_ICONERROR);
        return 0;
    }

    //2) Создание окна:
    
    HWND hwnd = CreateWindowEx(
        0,
        g_sz_MY_WINDOW_CLASS,   //Имя класса окна
        g_sz_MY_WINDOW_CLASS,   //Заголовок окна
        WS_OVERLAPPEDWINDOW, //Стиль окна для главного окна программы всегда будет WS_OVERLAPPEDWINDOW - это окно верхнего уровня(TOP_LEVEL_WINDOW), которое включает в себя дочерний ....
        CW_USEDEFAULT,CW_USEDEFAULT, //Начальная позицция окна
        CW_USEDEFAULT,CW_USEDEFAULT, //Размер окна
        NULL, //Parent Window
        NULL, //Для главного окна это меню. Для дочернего окна это ID его ресурса (IDC_EDIT)
        hInstance,
        NULL);
    
    if (hwnd == 0)
    {
        MessageBox(NULL, "Окно не было созданно", "Error", MB_OK | MB_ICONERROR);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow); // Задает режим отоброжения окна
    UpdateWindow(hwnd); // Выполняет прорисовку окна



    //3) Запуск цикла сообщений:

    MSG msg;
    while (GetMessage(&msg, NULL, 0 , 0) > 0)
    {
        TranslateMessage(&msg); // Транслирует сообщения виртуальных клавищ в символьные сообщения
        DispatchMessage(&msg); // Отправляет сообщение процедуре окна. Сообщение берет от GetMessage();
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
    case WM_CLOSE: 
        if(MessageBox(hwnd, "Вы действительно хотите закрыть окно?", "Question", MB_YESNO | MB_ICONQUESTION) == IDYES)
            DestroyWindow(hwnd); 
        
        break;
    default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }


    return 0;
}