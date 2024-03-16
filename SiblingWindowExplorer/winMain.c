#include "winMain.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Perform application initialization:
    if (!InitMainWinInstance(nCmdShow))
    {
        return FALSE;
    }

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

//
//   FUNCTION: InitMainWinInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//
BOOL InitMainWinInstance(int nCmdShow)
{
    RegisterMainWinClass();

    hWndMain = CreateWindowEx(NULL, szMainWinClass, L"MainWin", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, GetModuleHandle(NULL), NULL);

    if (!hWndMain)
    {
        return FALSE;
    }

    ShowWindow(hWndMain, nCmdShow);
    UpdateWindow(hWndMain);

    return TRUE;
}

//
//  FUNCTION: RegisterMainWinClass()
//
//  PURPOSE: Registers the window class.
//
ATOM RegisterMainWinClass()
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = MainWndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = GetModuleHandle(NULL);
    wcex.hIcon = NULL;
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szMainWinClass;
    wcex.hIconSm = NULL;

    return RegisterClassEx(&wcex);
}

//
//  FUNCTION: MainWndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_CREATE:
        {
            if (!InitChildWindows(hWnd, 3))
            {
                return -1L;
            }
            if (!InitButtons(hWnd))
            {
                return -1L;
            }
            return 0L;
        }

        case WM_COMMAND:
        {
            return OnMainWinCommand(hWnd, LOWORD(wParam));
        }

        case WM_SIZE:
        {
            return OnMainWinSize((UINT)wParam, (int32_t)LOWORD(lParam), (int32_t)HIWORD(lParam));
        }

        case WM_PAINT:
        {
            return OnMainWinPaint();
        }

        case WM_DESTROY:
        {
            PostQuitMessage(0);
        }
        break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT	OnMainWinCommand(HWND hWnd, int wmId)
{
    DWORD style = 0;

    switch (wmId)
    {
        case applyButton:
        {
            if ((SendMessage(hWndButtons[0], BM_GETSTATE, NULL, NULL) & BST_CHECKED) == BST_CHECKED)
            {
                style = 0;
                style = (DWORD)GetWindowLongPtr(hWndChildren[0], GWL_STYLE);
                style |= WS_CLIPSIBLINGS;
                SetWindowLongPtr(hWndChildren[0], GWL_STYLE, (LONG_PTR)style);
                SetWindowPos(hWndChildren[0], 0, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
                style = 0;
                style = (DWORD)GetWindowLongPtr(hWndChildren[2], GWL_STYLE);
                style |= WS_CLIPSIBLINGS;
                SetWindowLongPtr(hWndChildren[2], GWL_STYLE, (LONG_PTR)style);
                SetWindowPos(hWndChildren[2], 0, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
            }
            else
            {
                style = 0;
                style = (DWORD)GetWindowLongPtr(hWndChildren[0], GWL_STYLE);
                style &= ~(WS_CLIPSIBLINGS);
                SetWindowLongPtr(hWndChildren[0], GWL_STYLE, (LONG_PTR)style);
                SetWindowPos(hWndChildren[0], 0, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
                style = 0;
                style = (DWORD)GetWindowLongPtr(hWndChildren[2], GWL_STYLE);
                style &= ~(WS_CLIPSIBLINGS);
                SetWindowLongPtr(hWndChildren[2], GWL_STYLE, (LONG_PTR)style);
                SetWindowPos(hWndChildren[2], 0, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
            }

            if ((SendMessage(hWndButtons[1], BM_GETSTATE, NULL, NULL) & BST_CHECKED) == BST_CHECKED)
            {
                SetWindowPos(hWndChildren[0], HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER);
                SetWindowPos(hWndChildren[2], HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER);
            } 

            if ((SendMessage(hWndButtons[2], BM_GETSTATE, NULL, NULL) & BST_CHECKED) == BST_CHECKED)
            {
                SetWindowPos(hWndChildren[1], hWndChildren[0], 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER);
                SetWindowPos(hWndChildren[2], hWndChildren[1], 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER);
            }

            if ((SendMessage(hWndButtons[3], BM_GETSTATE, NULL, NULL) & BST_CHECKED) == BST_CHECKED)
            {
                drawOrderA = TRUE;
            }
            else
            {
                drawOrderA = FALSE;
            }
    
            if ((SendMessage(hWndButtons[4], BM_GETSTATE, NULL, NULL) & BST_CHECKED) == BST_CHECKED)
            {
                style = 0;
                style = (DWORD)GetWindowLongPtr(hWndChildren[1], GWL_STYLE);
                style |= WS_CLIPSIBLINGS;
                SetWindowLongPtr(hWndChildren[1], GWL_STYLE, (LONG_PTR)style);
                SetWindowPos(hWndChildren[1], 0, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
            }
            else
            {
                style = 0;
                style = (DWORD)GetWindowLongPtr(hWndChildren[1], GWL_STYLE);
                style &= ~(WS_CLIPSIBLINGS);
                SetWindowLongPtr(hWndChildren[1], GWL_STYLE, (LONG_PTR)style);
                SetWindowPos(hWndChildren[1], 0, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
            }

            if ((SendMessage(hWndButtons[5], BM_GETSTATE, NULL, NULL) & BST_CHECKED) == BST_CHECKED)
            {
                SetWindowPos(hWndChildren[1], HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER);
            }

            if ((SendMessage(hWndButtons[6], BM_GETSTATE, NULL, NULL) & BST_CHECKED) == BST_CHECKED)
            {
                SetWindowPos(hWndChildren[1], hWndChildren[2], 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER);
                SetWindowPos(hWndChildren[0], hWndChildren[1], 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER);
            }

            if ((SendMessage(hWndButtons[7], BM_GETSTATE, NULL, NULL) & BST_CHECKED) == BST_CHECKED)
            {
                drawOrderB = TRUE;
            }
            else
            {
                drawOrderB = FALSE;
            }

            // Force resize
            RECT rcClient = { 0 };
            GetClientRect(hWnd, &rcClient);
            OnMainWinSize(0, (int32_t)(rcClient.right - rcClient.left - 3), (int32_t)(rcClient.bottom - rcClient.top - 3));
            OnMainWinSize(0, (int32_t)(rcClient.right - rcClient.left), (int32_t)(rcClient.bottom - rcClient.top));
            RedrawWindow(hWnd, 0, 0, RDW_ERASE | RDW_INTERNALPAINT | RDW_ALLCHILDREN | RDW_UPDATENOW);
        }
        break;
    }
    return 0L;
}

LRESULT OnMainWinSize(UINT state, int32_t xClientArea, int32_t yClientArea)
{
    for (int i = 0; i < buttonCount; i++)
    {
        if (i < 3)
        {
            // Size and position the child window.  
            BOOL b = TRUE;
            if (drawOrderA || drawOrderB)
            {
                b = FALSE;
            }
            MoveWindow(hWndChildren[i],
                (xClientArea / 3) * i,
                (yClientArea / 3) * i,
                (xClientArea / 3) + 25,
                (yClientArea / 3) + 25,
                b);
        }

        if (i < 4)
        {
            MoveWindow(hWndButtons[i], (xClientArea - 400), (30 + (50 * i)), 140, 30, TRUE);
        }
        if ((i >= 4) && (i < 8))
        {
            MoveWindow(hWndButtons[i], (xClientArea - 200), (30 + (50 * (i - 4))), 140, 30, TRUE);
        }
        if (i == 8)
        {
            MoveWindow(hWndButtons[i], (xClientArea - 200), (30 + (50 * (i - 4))), 80, 30, TRUE);
        }
    }

    return 0L;
}

LRESULT OnMainWinPaint()
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWndMain, &ps);
    // TODO: Add any drawing code that uses hdc here...
    TextOut(hdc, (ps.rcPaint.right - 400), 10, (LPCWSTR)(L"Area 1 & 3"), 11);
    TextOut(hdc, (ps.rcPaint.right - 200), 10, (LPCWSTR)(L"Area 2"), 7);
    TextOut(hdc, (ps.rcPaint.right - 400), 230, (LPCWSTR)(L"*check 1 box only"), 18);
    TextOut(hdc, (ps.rcPaint.right - 400), 280, (LPCWSTR)(L"**A window resize may be required to observe changes"), 54);
    EndPaint(hWndMain, &ps);

    if (drawOrderA)
    {
        RedrawWindow(hWndChildren[0], 0, 0, RDW_ERASE | RDW_INTERNALPAINT | RDW_ALLCHILDREN | RDW_UPDATENOW);
        RedrawWindow(hWndChildren[2], 0, 0, RDW_ERASE | RDW_INTERNALPAINT | RDW_ALLCHILDREN | RDW_UPDATENOW);
        RedrawWindow(hWndChildren[1], 0, 0, RDW_ERASE | RDW_INTERNALPAINT | RDW_ALLCHILDREN | RDW_UPDATENOW);
    }
    if (drawOrderB)
    {
        RedrawWindow(hWndChildren[1], 0, 0, RDW_ERASE | RDW_INTERNALPAINT | RDW_ALLCHILDREN | RDW_UPDATENOW);
        RedrawWindow(hWndChildren[0], 0, 0, RDW_ERASE | RDW_INTERNALPAINT | RDW_ALLCHILDREN | RDW_UPDATENOW);
        RedrawWindow(hWndChildren[2], 0, 0, RDW_ERASE | RDW_INTERNALPAINT | RDW_ALLCHILDREN | RDW_UPDATENOW);
    }

    return 0L;
}


BOOL InitButtons(HWND hWnd)
{
    int i = 0;
    RECT rc;
    GetClientRect(hWnd, &rc);

    hWndButtons[i] = CreateWindowExW(
        NULL,
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"Clip Siblings",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,  // Styles 
        (rc.right - 200),         // x position 
        20,         // y position 
        125,        // Button width
        30,        // Button height
        hWnd,     // Parent window
        NULL,       // No menu.
        GetModuleHandle(NULL),
        NULL);      // Pointer not needed.

    if (hWndButtons[i])
    {
        i++;
    }
    else
    {
        return FALSE;
    }


    hWndButtons[i] = CreateWindowEx(
        NULL,
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"Z-Order Top",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,  // Styles 
        (rc.right - 200),         // x position 
        20,         // y position 
        125,        // Button width
        30,        // Button height
        hWnd,     // Parent window
        NULL,       // No menu.
        GetModuleHandle(NULL),
        NULL);      // Pointer not needed.

    if (hWndButtons[i])
    {
        i++;
    }
    else
    {
        return FALSE;
    }


    hWndButtons[i] = CreateWindowEx(
        NULL,
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"Z-Order 1, 2, 3",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,  // Styles 
        (rc.right - 200),         // x position 
        20,         // y position 
        125,        // Button width
        30,        // Button height
        hWnd,     // Parent window
        NULL,       // No menu.
        GetModuleHandle(NULL),
        NULL);      // Pointer not needed.

    if (hWndButtons[i])
    {
        i++;
    }
    else
    {
        return FALSE;
    }


    hWndButtons[i] = CreateWindowEx(
        NULL,
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"DrawOrder  1, 3, 2",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,  // Styles 
        (rc.right - 200),         // x position 
        20,         // y position 
        125,        // Button width
        30,        // Button height
        hWnd,     // Parent window
        NULL,       // No menu.
        GetModuleHandle(NULL),
        NULL);      // Pointer not needed.

    if (hWndButtons[i])
    {
        i++;
    }
    else
    {
        return FALSE;
    }


    hWndButtons[i] = CreateWindowEx(
        NULL,
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"Clip Siblings",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,  // Styles 
        (rc.right - 200),         // x position 
        20,         // y position 
        125,        // Button width
        30,        // Button height
        hWnd,     // Parent window
        NULL,       // No menu.
        GetModuleHandle(NULL),
        NULL);      // Pointer not needed.

    if (hWndButtons[i])
    {
        i++;
    }
    else
    {
        return FALSE;
    }


    hWndButtons[i] = CreateWindowEx(
        NULL,
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"Z-Order Top",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,  // Styles 
        (rc.right - 200),         // x position 
        20,         // y position 
        125,        // Button width
        30,        // Button height
        hWnd,     // Parent window
        NULL,       // No menu.
        GetModuleHandle(NULL),
        NULL);      // Pointer not needed.

    if (hWndButtons[i])
    {
        i++;
    }
    else
    {
        return FALSE;
    }


    hWndButtons[i] = CreateWindowEx(
        NULL,
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"Z-Order 3, 2, 1",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,  // Styles 
        (rc.right - 200),         // x position 
        20,         // y position 
        125,        // Button width
        30,        // Button height
        hWnd,     // Parent window
        NULL,       // No menu.
        GetModuleHandle(NULL),
        NULL);      // Pointer not needed.

    if (hWndButtons[i])
    {
        i++;
    }
    else
    {
        return FALSE;
    }


    hWndButtons[i] = CreateWindowEx(
        NULL,
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"Draw Order 2, 1, 3",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,  // Styles 
        (rc.right - 200),         // x position 
        20,         // y position 
        125,        // Button width
        30,        // Button height
        hWnd,     // Parent window
        NULL,       // No menu.
        GetModuleHandle(NULL),
        NULL);      // Pointer not needed.

    if (hWndButtons[i])
    {
        i++;
    }
    else
    {
        return FALSE;
    }

    hWndButtons[i] = CreateWindowEx(
        NULL,
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"Apply",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        (rc.right - 200),         // x position 
        200,         // y position 
        125,        // Button width
        30,        // Button height
        hWnd,     // Parent window
        applyButton,       // Id.
        GetModuleHandle(NULL),
        NULL);      // Pointer not needed.

    if (!hWndButtons[i])
    {
        return FALSE;
    }

    return TRUE;
}