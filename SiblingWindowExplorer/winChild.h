/*** Includes ***/
#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <Windows.h>

#include <strsafe.h>

/*** Defines **/


/*** Variable declarations ***/
extern TCHAR szChildWinClass[];	// The children window class name.
extern HWND	hWndChildren[3];


/*** Forward declarations of functions included in this code module: ***/
BOOL				InitChildWindows(HWND hWnd, int nWindows);
ATOM                RegisterChildWinClass();
LRESULT CALLBACK    ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
