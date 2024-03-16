#include "winChild.h"

TCHAR szChildWinClass[] = L"ChildWindow";
HWND hWndChildren[3] = { 0 };

BOOL InitChildWindows(HWND hWnd, int nWindows)
{
	nWindows--;

    RegisterChildWinClass();

    const wchar_t* childBuffer = L"ChildWindow";
    wchar_t numBuffer[2] = L"";
    wchar_t buffer[17] = L"";

    for (int i = 0; i <= nWindows; i++)
    {
        if (FAILED(StringCchCopyW(buffer, 15, childBuffer)))
        {
            return FALSE;
        }

        _itow_s(i, numBuffer, 2, 10);

        if (FAILED(StringCchCatW(buffer, 16, numBuffer)))
        {
            return FALSE;
        }

        hWndChildren[i] = CreateWindowEx(0, szChildWinClass, buffer, WS_CHILD | WS_BORDER | WS_VISIBLE | WS_CLIPCHILDREN,
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hWnd, NULL, GetModuleHandle(NULL), NULL);
    }
    return TRUE;
}

ATOM RegisterChildWinClass()
{
    WNDCLASSEXW wcex = {0};

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = ChildWndProc;
    wcex.hInstance = GetModuleHandle(NULL);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszClassName = szChildWinClass;
    if (!RegisterClassExW(&wcex))
    {
        //handle error
    }
}

LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0L;
        }

        case WM_PAINT:
        {
            // Beginpaint and endpaint validate the rect so the pain message isn't resent
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);

            //int i = GetWindowLong(hWnd, GWL_ID) - IDC_CONTROLIDBASE;
            wchar_t Buffer[16] = L"";
            GetWindowText(hWnd, Buffer, 16);
            OutputDebugString(Buffer);
            OutputDebugString(L": Painted\n");

            return 0L;
        }
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}