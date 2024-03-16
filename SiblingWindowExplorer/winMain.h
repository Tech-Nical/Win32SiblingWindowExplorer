/*** Includes ***/
#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <Windows.h>

#include <stdint.h>

#include "winChild.h"

/*** Defines **/
#define buttonCount				9
#define applyButton				60000

/*** Variable declarations ***/
TCHAR	szMainWinClass[] = L"MainWindow";	// The main window class name.
HWND	hWndMain = { 0 };
HWND	hWndButtons[buttonCount] = { 0 };
BOOL	drawOrderA = FALSE;
BOOL	drawOrderB = FALSE;


/*** Forward declarations of functions included in this code module: ***/
BOOL                InitMainWinInstance(int nCmdShow);
ATOM                RegisterMainWinClass();
LRESULT CALLBACK    MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT				OnMainWinCommand(HWND hWnd, int wmId);
LRESULT				OnMainWinSize(UINT state, int32_t xClientArea, int32_t yClientArea);
LRESULT				OnMainWinPaint();
BOOL				InitButtons(HWND hWnd);

