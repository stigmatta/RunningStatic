#include <windows.h>
#include <tchar.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

HWND hStatic1;
HINSTANCE hInst;
UINT nStaticCounter = 0;
 int WIDTH = 100, HEIGHT = 100, TOP = 50, LEFT = 200;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
    hInst = hInstance;
    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CLOSE:
        EndDialog(hWnd, 0); // закрываем модальный диалог
        return TRUE;

    case WM_INITDIALOG:
        hStatic1 = CreateWindowEx(0, TEXT("STATIC"), TEXT("CLICK ME"),
            WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | WS_EX_CLIENTEDGE,
            LEFT, TOP, WIDTH, HEIGHT, hWnd, 0, hInst, 0);
        return TRUE;

    case WM_MOUSEMOVE:
    {
        RECT StaticRect;
        GetWindowRect(hStatic1, &StaticRect);
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);

        if (y >= StaticRect.top && y <= StaticRect.bottom) {
            if (x >= StaticRect.left - 30 && x <= StaticRect.left - 10) {
                LEFT += 5;
                MoveWindow(hStatic1, LEFT, TOP, StaticRect.right - StaticRect.left, HEIGHT, TRUE);
            }
            else if (x <= StaticRect.right + 30 && x >= StaticRect.right + 10)
            {
                LEFT -= 5;
                MoveWindow(hStatic1, LEFT, TOP, StaticRect.right - StaticRect.left, HEIGHT, TRUE);
            }
        }
        if (x >= StaticRect.left && x <= StaticRect.right) {
            if (y >= StaticRect.top - 30 && y <= StaticRect.top - 10) {
                TOP += 5;
                MoveWindow(hStatic1, LEFT, TOP, WIDTH, StaticRect.bottom - StaticRect.top, TRUE);
            }
            else if (y <= StaticRect.bottom + 30 && y >= StaticRect.bottom + 10){
            
                TOP -= 5;
                MoveWindow(hStatic1, LEFT, TOP, WIDTH, StaticRect.bottom - StaticRect.top, TRUE);
            }
        }
      
        break;
    }

    }
    return FALSE;
}
