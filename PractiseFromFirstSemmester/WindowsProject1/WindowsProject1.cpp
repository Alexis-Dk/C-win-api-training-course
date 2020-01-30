﻿// WindowsProject1.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "WindowsProject1.h"
#include "resource.h"
#include "psapi.h"
#include <stdio.h>

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
SECURITY_ATTRIBUTES sa;
HWND hWnd;
WCHAR mainTitleText[MAX_LOADSTRING] = L"Custom main titile";
WCHAR secondTitleText[MAX_LOADSTRING] = L"Second dialog title";
LPCTSTR strGlobal = L"";
LPARAM strListGlobal = (LPARAM)L"";

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK OpenDialog(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//

DWORD WINAPI TrackBarThreadOne(PVOID pvParam)
{
    DWORD NumB;
    // должно быть с k
    //k = _wtoi(pArgv[1]);
    //hFile = (HANDLE)k;
    
    HANDLE hFile = CreateFile(L"C:\\Users\\adruzik\\Source\\Repos\\Alexis-Dk\\C-win-api-training-course\\Lab7\\7 работа\\Laba 7\\file.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
        &sa, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    //SetDlgItemInt(hWnd, IDE_EDIT1, 1000, FALSE); // вместо 1000 - k
    SetFilePointer(hFile, 0, NULL, FILE_END);
    WriteFile(hFile, "text", strlen("text"), &NumB, NULL);
    MessageBox(hWnd, L"Запись в файл прошла успешно!!!", L"Information", MB_OK | MB_ICONINFORMATION);
    CloseHandle(hFile);
    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HANDLE hFile;
    TCHAR cmdproc2[] = L"C:\\Users\\adruzik\\Source\\Repos\\Alexis-Dk\\C-win-api-training-course\\Lab7\\7 работа\\Process 2\\Debug\\Process 2.exe";
    TCHAR notepad[] = L"Notepad";
    TCHAR paint[] = L"C:\\Windows\\system32\\mspaint.exe";
    static HANDLE hThread;
    DWORD dTs;
    DWORD dwBytes;
    int end;
    char BinFile[200] = "";
    char buf[1000];
    int dataInt;
    float dataFloatPrimitive;
    double dataDoublePrimitive;
    FLOAT dataFloat;
    LONG dataLong;
    char q[200] = "";
    char BinnFile[200] = "";
    HANDLE hwndBin;
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            DWORD size, NumB;
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case ID_FILE_WRITE:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                hFile = CreateFile(L"C:\\Users\\Alex\\Desktop\\file1.txt", GENERIC_READ | GENERIC_WRITE,
                    FILE_SHARE_READ | FILE_SHARE_WRITE,
                    &sa, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
                //SetDlgItemInt(hWnd, IDE_EDIT1, 1000, FALSE); // вместо 1000 - k
                SetFilePointer(hFile, 0, NULL, FILE_END);

                WriteFile(hFile, "Alexey\r\n", strlen("Alexey\r\n"), &NumB, NULL);
                WriteFile(hFile, "Druzik\r\n", strlen("Druzik\r\n"), &NumB, NULL);
                MessageBox(hWnd, L"Запись в файл прошла успешно!!!", L"Information", MB_OK | MB_ICONINFORMATION);
                CloseHandle(hFile);
                break;
            case ID_FILE_READ:

                hFile = CreateFile(L"C:\\Users\\adruzik\\Source\\Repos\\Alexis-Dk\\C-win-api-training-course\\Lab7\\7 работа\\Laba 7\\file.txt", GENERIC_READ | GENERIC_WRITE,
                    FILE_SHARE_READ | FILE_SHARE_READ,
                    &sa, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

                size = GetFileSize(hFile, NULL);
                SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
                ReadFile(hFile, buf, size, &NumB, NULL);
                buf[size] = '\0';
                MessageBoxA(hWnd, buf, "Information", MB_OK | MB_ICONINFORMATION);
                //SetDlgItemTextA(hWnd, IDC_EDIT1, buf);//
                break;
            case ID_PROCESS_CREATE:
                STARTUPINFO si;
                PROCESS_INFORMATION pi;
                ZeroMemory(&si, sizeof(si));
                si.cb = sizeof(si);
                ZeroMemory(&pi, sizeof(pi));
                CreateProcess(NULL, paint, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
                SetPriorityClass(GetCurrentProcess(), DETACHED_PROCESS);

                DWORD dwProcessPriority;
                dwProcessPriority = GetPriorityClass(GetCurrentProcess());

                if (dwProcessPriority > 0) {
                    if (dwProcessPriority & REALTIME_PRIORITY_CLASS) {
                        printf("Highest priority process.\n");
                    }
                    if (dwProcessPriority & HIGH_PRIORITY_CLASS) {
                        printf("High priority process.\n");
                    }
                    if (dwProcessPriority & NORMAL_PRIORITY_CLASS) {
                        printf("Normal priority process.\n");
                    }
                    if (dwProcessPriority & IDLE_PRIORITY_CLASS) {
                        printf("Background process.\n");
                    }
                }

                DWORD aProcesses[1024], cbNeeded, cProcesses;
                unsigned int i;

                if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
                {
                    return 1;
                }
                cProcesses = cbNeeded / sizeof(DWORD);
                for (i = 0; i < cProcesses; i++)
                {
                    if (aProcesses[i] != 0)
                    {
                        TCHAR a[] = L"";
                    }
                }
                break;
            case ID_SETEDITANDLIST_CHANGEEDIT:
                strGlobal = L"123";
                strListGlobal = (LPARAM)L"Line1";
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, OpenDialog);
                //DialogBox(hInst, L"DIALOG_OPEN_FILE", hWnd, (DLGPROC)OpenDialog);
                break;
            case ID_SETEDITANDLIST_CHANGELIST:
                strGlobal = L"346";
                strListGlobal = (LPARAM)L"Line2";
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, OpenDialog);
                //DialogBox(hInst, L"DIALOG_OPEN_FILE", hWnd, (DLGPROC)OpenDialog);
                break;
            case ID_CHANGEWINDOWTITLE_CHANGE:
                SetWindowText(hWnd, mainTitleText);
                break;
            case ID_THREAD_CREATETHREAD:
                hThread = CreateThread(NULL, 0, TrackBarThreadOne,
                    NULL, 0, &dTs);
                break;
            case ID_WRITEDIFFERENTTYPESTOBINFILE_WRITE:
            {
                hwndBin = CreateFile(L"C:\\Users\\Alex\\Source\\Repos\\Alexis-Dk\\C-win-api-training-course\\file.bin", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
                //if (hwndBin == INVALID_HANDLE_VALUE) {
                //    MessageBox(hWnd, L"Ошибка", L"Ошибка", MB_OK | MB_ICONWARNING);
                //}
                //DWORD size;

                //int dataInt;
                //float dataFloatPrimitive;
                //double dataDoublePrimitive;
                //FLOAT dataFloat;
                //LONG dataLong;

                dataInt = 100;
                dataFloatPrimitive = 1.123;
                dataDoublePrimitive = 1.000;
                dataFloat = 1.1;
                dataLong = 300;

                WriteFile(hwndBin, &dataInt, sizeof(int), &dwBytes, NULL);
                WriteFile(hwndBin, &dataFloatPrimitive, sizeof(float), &dwBytes, NULL);
                WriteFile(hwndBin, &dataDoublePrimitive, sizeof(double), &dwBytes, NULL);
                WriteFile(hwndBin, &dataFloat, sizeof(FLOAT), &dwBytes, NULL);
                WriteFile(hwndBin, &dataLong, sizeof(LONG), &dwBytes, NULL);

                CloseHandle(hwndBin);
            }
                break;
            case ID_READDIFFERENTTYPESFROMBINFILE_READ:
            {
                hwndBin = CreateFile(L"C:\\Users\\Alex\\Source\\Repos\\Alexis-Dk\\C-win-api-training-course\\file.bin", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL);
                end = GetFileSize(hwndBin, NULL);
                SetFilePointer(hwndBin, 0, NULL, FILE_BEGIN);
                ReadFile(hwndBin, BinFile, end, &dwBytes, NULL);
                SetFilePointer(hwndBin, 0, NULL, FILE_BEGIN);

                ReadFile(hwndBin, &dataInt, sizeof(int), &dwBytes, NULL);
                sprintf_s(q, "%i ", dataInt);
                strcat_s(BinnFile, q);

                ReadFile(hwndBin, &dataFloatPrimitive, sizeof(float), &dwBytes, NULL);
                sprintf_s(q, "%.2f ", dataFloatPrimitive);
                strcat_s(BinnFile, q);

                ReadFile(hwndBin, &dataDoublePrimitive, sizeof(double), &dwBytes, NULL);
                sprintf_s(q, "%.2f ", dataDoublePrimitive);
                strcat_s(BinnFile, q);

                ReadFile(hwndBin, &dataFloat, sizeof(FLOAT), &dwBytes, NULL);
                sprintf_s(q, "%.2f ", dataFloat);
                strcat_s(BinnFile, q);

                ReadFile(hwndBin, &dataLong, sizeof(LONG), &dwBytes, NULL);
                sprintf_s(q, "%d ", dataLong);
                strcat_s(BinnFile, q);

                CloseHandle(hwndBin);
            }
                break;
            case WM_PAINT:
                {
                    PAINTSTRUCT ps;
                    HDC hdc = BeginPaint(hWnd, &ps);
                    // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
                    EndPaint(hWnd, &ps);
                }
                break;
            case WM_DESTROY:
                PostQuitMessage(0);
                break; 
            } }
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
            return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK OpenDialog(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    //int IDC_EDIT[12] = { IDC_EDIT1, IDC_EDIT2};

    switch (message)
    {
    case WM_INITDIALOG:

        HWND hEdit;
        hEdit = GetDlgItem(hwnd, IDC_EDIT2);
        SetDlgItemText(hwnd, IDC_EDIT2, strGlobal);

        HWND hList;
        hList = GetDlgItem(hwnd, IDC_LIST1);
        SendMessage(hList, LB_ADDSTRING, 0, strListGlobal);

        SetWindowText(hWnd, secondTitleText);

        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hwnd, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}